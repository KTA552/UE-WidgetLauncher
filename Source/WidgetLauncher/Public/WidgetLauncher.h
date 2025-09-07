// Copyright (c) 2025 Keita Nakamura

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FWidgetLauncherUIManager;

class FWidgetLauncherModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// メニュー再構築用API
	void RebuildMenus();

	// モジュールアクセサ
	static FWidgetLauncherModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FWidgetLauncherModule>(TEXT("WidgetLauncher"));
	}

private:
	TSharedPtr<FWidgetLauncherUIManager> UIManager;
};
