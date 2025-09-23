// Copyright (c) 2025 Keita Nakamura

using UnrealBuildTool;

public class WidgetLauncher : ModuleRules
{
	public WidgetLauncher(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"EditorSubsystem",
				"EditorWidgets",
				"EditorStyle",
				"UMG",
				"UMGEditor",
				"Blutility",
				"InputCore",
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Slate",
				"SlateCore",
				"ToolMenus",
				"EditorStyle",
				"EditorWidgets",
				"UnrealEd",
				"LevelEditor",
				"WorkspaceMenuStructure",
				"PropertyEditor",
				"SettingsEditor",
				"DeveloperSettings",
			}
		);
	}
}
