// Copyright (c) 2025 Keita Nakamura

#include "WidgetLauncherUIManager.h"
#include "WidgetLauncherSettings.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "Framework/Application/SlateApplication.h"
#include "ToolMenus.h"
#include "Engine/Engine.h"
#include "Styling/AppStyle.h"

#define LOCTEXT_NAMESPACE "WidgetLauncher"

void FWidgetLauncherUIManager::Initialize()
{
	if (UToolMenus::IsToolMenuUIEnabled())
	{
		UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FWidgetLauncherUIManager::RegisterMenu));
	}
	RefreshAvailableWidgets();
}

void FWidgetLauncherUIManager::Shutdown()
{
	AllWidgetInfos.Empty();
}

void FWidgetLauncherUIManager::Unregister()
{
	if (!UToolMenus::IsToolMenuUIEnabled()) return;
	if (!UToolMenus::Get()) return;
	// ツールバーのエントリを除去
	if (UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.User");
		Menu->FindSection("WidgetLauncherToolbarSection"))
	{
		Menu->RemoveSection("WidgetLauncherToolbarSection");
	}
	// ステータスバーのエントリを除去
	if (UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.StatusBar.ToolBar");
		Menu->FindSection("WidgetLauncherStatusBarSection"))
	{
		Menu->RemoveSection("WidgetLauncherStatusBarSection");
	}
	// メニューバー(Window)のエントリを除去
	if (UToolMenu* WindowMenu = UToolMenus::Get()->FindMenu("LevelEditor.MainMenu.Window"))
	{
		if (FToolMenuSection* Section = WindowMenu->FindSection("WidgetLauncherWindowSection"))
		{
			WindowMenu->RemoveSection("WidgetLauncherWindowSection");
		}
	}
}

void FWidgetLauncherUIManager::RegisterMenu()
{
	const UWidgetLauncherSettings* Settings = GetDefault<UWidgetLauncherSettings>();
	if (!Settings->bIsEnabled)
	{
		return;
	}

	switch (Settings->WidgetLauncherLocation)
	{
	case EWidgetLauncherLocation::ToolBar:
	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.User");
		FToolMenuSection& ToolbarSection = ToolbarMenu->FindOrAddSection("WidgetLauncherToolbarSection", LOCTEXT("WidgetLauncherSection", "Widget Launcher"));
		ToolbarSection.AddEntry(FToolMenuEntry::InitComboButton(
			"WidgetLauncherToolbarButton",
			FUIAction(),
			FOnGetContent::CreateRaw(this, &FWidgetLauncherUIManager::GenerateWidgetLauncherEntry),
			LOCTEXT("WidgetLauncher", "Widget Launcher"),
			LOCTEXT("WidgetLauncherTooltip", "Launch Editor Utility Widgets"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "LauncherCommand.QuickLaunch")
		));
		break;
	}
	case EWidgetLauncherLocation::MenuBar:
	{
		// Window メニューにサブメニューとして追加
		UToolMenu* WindowMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		FToolMenuSection& Section = WindowMenu->FindOrAddSection("WidgetLauncherWindowSection", LOCTEXT("WidgetLauncherWindowSection", "Widget Launcher"));
		Section.AddSubMenu(
			"WidgetLauncherMainMenu",
			LOCTEXT("WidgetLauncherWindowMenu", "Widget Launcher"),
			FText::GetEmpty(),
			FNewMenuDelegate::CreateLambda([this](FMenuBuilder& SubMenuBuilder)
			{
				BuildCategoryMenus(SubMenuBuilder);
			})
		);
		break;
	}
	case EWidgetLauncherLocation::StatusBar:
	{
		// ステータスバーにボタン追加
		UToolMenu* StatusBarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.StatusBar.ToolBar");
		FToolMenuSection& Section = StatusBarMenu->FindOrAddSection("WidgetLauncherStatusBarSection", LOCTEXT("WidgetLauncherStatusBarSection", "Widget Launcher"));
		Section.AddEntry(FToolMenuEntry::InitComboButton(
			"WidgetLauncherStatusBarButton",
			FUIAction(),
			FOnGetContent::CreateRaw(this, &FWidgetLauncherUIManager::GenerateWidgetLauncherEntry),
			LOCTEXT("WidgetLauncher", ""),
			LOCTEXT("WidgetLauncherTooltip", "Launch Editor Utility Widgets"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "LauncherCommand.QuickLaunch")
		));
		break;
	}
	default:
		break;
	}
}

void FWidgetLauncherUIManager::RefreshAvailableWidgets()
{
	AllWidgetInfos.Empty();
	
	const UWidgetLauncherSettings* Settings = GetDefault<UWidgetLauncherSettings>();
	if (Settings)
	{
		AllWidgetInfos = Settings->WidgetInfos;
	}
}

TSharedRef<SWidget> FWidgetLauncherUIManager::GenerateWidgetLauncherEntry()
{
	// 設定を再読み込み
	RefreshAvailableWidgets();
	
	FMenuBuilder MenuBuilder(true, nullptr);
	
	// カテゴリ別にメニューを構築（検索なし）
	BuildCategoryMenus(MenuBuilder);
	
	return MenuBuilder.MakeWidget();
}

void FWidgetLauncherUIManager::BuildCategoryMenus(FMenuBuilder& MenuBuilder)
{
	// カテゴリごとにWidgetInfoをグループ化
	TMap<FString, TArray<FWidgetLauncherCategoryInfo>> CategoryGroups;
	
	for (const FWidgetLauncherCategoryInfo& WidgetInfo : AllWidgetInfos)
	{
		if (!WidgetInfo.EditorUtilityWidget.IsNull())
		{
			FString Category = WidgetInfo.CategoryName;
			if (Category.Contains(TEXT("/")))
			{
				Category.Split(TEXT("/"), &Category, nullptr);
			}
			if (Category.IsEmpty())
			{
				Category = TEXT("Uncategorized");
			}
			CategoryGroups.FindOrAdd(Category).Add(WidgetInfo);
		}
	}
	
	if (CategoryGroups.Num() == 0)
	{
		MenuBuilder.AddMenuEntry(
			LOCTEXT("NoWidgetsFound", "No widgets found"),
			LOCTEXT("NoWidgetsFoundTooltip", "No Editor Utility Widgets are configured"),
			FSlateIcon(),
			FUIAction()
		);
		return;
	}
	
	for (const auto& CategoryPair : CategoryGroups)
	{
		const FString& CategoryName = CategoryPair.Key;
		const TArray<FWidgetLauncherCategoryInfo>& CategoryWidgets = CategoryPair.Value;
		
		MenuBuilder.AddSubMenu(
			FText::FromString(CategoryName),
			FText::GetEmpty(),
			FNewMenuDelegate::CreateLambda([CategoryWidgets](FMenuBuilder& SubMenuBuilder) {
				for (const FWidgetLauncherCategoryInfo& Widget : CategoryWidgets)
				{
					FString Label = !Widget.DisplayName.IsEmpty() ? Widget.DisplayName : Widget.EditorUtilityWidget.GetAssetName();
					if (Label.IsEmpty())
					{
						Label = Widget.EditorUtilityWidget.ToString();
					}
					SubMenuBuilder.AddMenuEntry(
						FText::FromString(Label),
						FText::GetEmpty(),
						FSlateIcon(),
						FUIAction(FExecuteAction::CreateLambda([Widget]() {
							if (UEditorUtilityWidgetBlueprint* LoadedWidget = Widget.EditorUtilityWidget.LoadSynchronous())
							{
								if (GEditor)
								{
									if (UEditorUtilitySubsystem* Subsys = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>())
									{
										Subsys->SpawnAndRegisterTab(LoadedWidget);
									}
								}
							}
						}))
					);
				}
			})
		);
	}
}

void FWidgetLauncherUIManager::AddToolbarEntry(class FToolBarBuilder& ToolbarBuilder)
{
	ToolbarBuilder.AddComboButton(
		FUIAction(),
		FOnGetContent::CreateRaw(this, &FWidgetLauncherUIManager::GenerateWidgetLauncherEntry),
		LOCTEXT("WidgetLauncher", "Widget Launcher"),
		LOCTEXT("WidgetLauncherTooltip", "Launch Editor Utility Widgets"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "LauncherCommand.QuickLaunch")
	);
}


#undef LOCTEXT_NAMESPACE
