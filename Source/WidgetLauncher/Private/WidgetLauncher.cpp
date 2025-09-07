// Copyright (c) 2025 Keita Nakamura

#include "WidgetLauncher.h"
#include "WidgetLauncherUIManager.h"

#define LOCTEXT_NAMESPACE "FWidgetLauncherModule"

void FWidgetLauncherModule::StartupModule()
{
	// UIManagerを初期化
	UIManager = MakeShareable(new FWidgetLauncherUIManager());
	UIManager->Initialize();
}

void FWidgetLauncherModule::ShutdownModule()
{
	// UIManagerをシャットダウン
	if (UIManager.IsValid())
	{
		UIManager->Shutdown();
		UIManager.Reset();
	}
}

void FWidgetLauncherModule::RebuildMenus()
{
	if (UIManager.IsValid())
	{
		UIManager->Unregister();
		UIManager->RegisterMenu();
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWidgetLauncherModule, WidgetLauncher)
