// Copyright (c) 2025 Keita Nakamura

#include "WidgetLauncherSettings.h"
#include "WidgetLauncher.h"

#define LOCTEXT_NAMESPACE "WidgetLauncher"

#if WITH_EDITOR
void UWidgetLauncherSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropName == GET_MEMBER_NAME_CHECKED(UWidgetLauncherSettings, bIsEnabled)
		|| PropName == GET_MEMBER_NAME_CHECKED(UWidgetLauncherSettings, WidgetLauncherLocation))
	{
		// メニューを再構築
		if (FModuleManager::Get().IsModuleLoaded(TEXT("WidgetLauncher")))
		{
			FWidgetLauncherModule::Get().RebuildMenus();
		}
	}
}

FText UWidgetLauncherSettings::GetSectionText() const
{
	return LOCTEXT("WidgetLauncherSectionName", "Widget Launcher");
}

FText UWidgetLauncherSettings::GetSectionDescription() const
{
	return LOCTEXT("WidgetLauncherSettingsDescription", "Configure the Widget Launcher plugin");
}
#endif

#undef LOCTEXT_NAMESPACE
