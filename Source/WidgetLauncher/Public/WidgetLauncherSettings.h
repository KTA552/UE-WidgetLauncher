// Copyright (c) 2025 Keita Nakamura

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "Engine/DeveloperSettings.h"
#include "WidgetLauncherSettings.generated.h"

USTRUCT(BlueprintType)
struct FWidgetLauncherCategoryInfo
{
	GENERATED_BODY()

	// カテゴリ名
	UPROPERTY(EditAnywhere, Category="Widget Launcher")
	FString CategoryName;

	// 表示名
	UPROPERTY(EditAnywhere, Category="Widget Launcher")
	FString DisplayName;

	UPROPERTY(EditAnywhere, Category="Widget Launcher")
	TSoftObjectPtr<UEditorUtilityWidgetBlueprint> EditorUtilityWidget;
};

UENUM(BlueprintType)
enum class EWidgetLauncherLocation : uint8
{
	MenuBar,
	ToolBar,
	StatusBar
};

UCLASS(config=EditorPerProjectUserSettings, defaultconfig, meta=(DisplayName="Widget Launcher"))
class WIDGETLAUNCHER_API UWidgetLauncherSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	virtual FName GetCategoryName() const override
	{
		return TEXT("Plugins");
	}

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual FText GetSectionText() const override;
	virtual FText GetSectionDescription() const override;
#endif
	
	// カテゴリとSoftObjectPathの配列
	UPROPERTY(EditAnywhere, config, Category="Widget Launcher")
	TArray<FWidgetLauncherCategoryInfo> WidgetInfos;

	UPROPERTY(EditAnywhere, config, Category="Widget Launcher")
	bool bIsEnabled = true;
	
	UPROPERTY(EditAnywhere, config, Category="Widget Launcher")
	EWidgetLauncherLocation WidgetLauncherLocation = EWidgetLauncherLocation::ToolBar;
};
