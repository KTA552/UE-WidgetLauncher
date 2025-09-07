// Copyright (c) 2025 Keita Nakamura

#pragma once

#include "CoreMinimal.h"
#include "WidgetLauncherSettings.h"

class WIDGETLAUNCHER_API FWidgetLauncherUIManager : public TSharedFromThis<FWidgetLauncherUIManager>
{
public:
	void Initialize();
	void Shutdown();
	void RegisterMenu();
	void Unregister();
	
	void AddToolbarEntry(class FToolBarBuilder& ToolbarBuilder);
	TSharedRef<SWidget> GenerateWidgetLauncherEntry();

private:
	void RefreshAvailableWidgets();
	void BuildCategoryMenus(class FMenuBuilder& MenuBuilder);
	
	TArray<FWidgetLauncherCategoryInfo> AllWidgetInfos;
};
