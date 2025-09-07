// Fill out your copyright notice in the Description page of Project Settings.

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

	// EditorUtilityWidgetのSoftObjectPath
	UPROPERTY(EditAnywhere, Category="Widget Launcher")
	TObjectPtr<UEditorUtilityWidgetBlueprint> EditorUtilityWidget;
};

UCLASS(config=EditorPerProjectUserSettings, defaultconfig, meta=(DisplayName="Widget Launcher"))
class WIDGETLAUNCHER_API UWidgetLauncherSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	// カテゴリとSoftObjectPathの配列
	UPROPERTY(EditAnywhere, config, Category="Widget Launcher")
	TArray<FWidgetLauncherCategoryInfo> WidgetInfos;

	UPROPERTY(EditAnywhere, config, Category="Widget Launcher")
	bool bIsEnabled = true;
	
	// メニューバーに表示
	UPROPERTY(EditAnywhere, config, Category="Widget Launcher", meta=(EditCondition="bIsEnabled"))
	bool bShowInMenuBar = true;

	// ツールバーに表示
	UPROPERTY(EditAnywhere, config, Category="Widget Launcher", meta=(EditCondition="bIsEnabled"))
	bool bShowInToolBar = true;

	// ステータスバーに表示
	UPROPERTY(EditAnywhere, config, Category="Widget Launcher", meta=(EditCondition="bIsEnabled"))
	bool bShowInStatusBar = false;
	
};
