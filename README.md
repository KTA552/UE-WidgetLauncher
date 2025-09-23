# Widget Launcher
https://github.com/user-attachments/assets/5d76dc3f-a9d6-44a6-8e54-4bc8605bd075

## Build Instructions

1. Place the plugin folder into your project's `Plugins` directory.
2. Open your project in Unreal Engine.
3. The plugin will be detected and built automatically. If not, right-click your `.uproject` file and select "Generate Visual Studio project files", then build the project from your IDE.

## How to Enable the Plugin

1. Open your Unreal Engine project.
2. Go to `Edit` > `Plugins`.
3. Search for "EditorUtilityWidget-Launcher".
4. Enable the plugin by checking the box.
5. Restart the editor if prompted.

## Usage
<img width="378" height="268" alt="image" src="https://github.com/user-attachments/assets/db1fdade-09a2-4933-8f83-c524f5bade99" />

A "Launcher" button will appear in the toolbar or status bar, depending on your settings.  
Click the button to open a list of registered Editor Utility Widgets (EUW).  
Select a widget from the list to launch it in the editor.

## How to Configure from Editor Preferences

<img width="1280" height="604" alt="image" src="https://github.com/user-attachments/assets/821ab146-6340-45ed-b6c2-b475d40d0a77" />

1. Go to `Edit` > `Editor Preferences`.
2. Find the "EditorUtilityWidget-Launcher" section in the sidebar.
3. You can configure the following settings:

- **Widget Infos**  
  Add or edit entries in the list.  
  - `CategoryName`: Set this to categorize your widgets. Widgets with the same `CategoryName` will be grouped together in the launcher.
  - `DisplayName`: This will be shown as the display name for the widget in the launcher UI.
  - `EditorUtilityWidget`: Select the Editor Utility Widget Blueprint you want to launch.

- **Is Enabled**  
  If unchecked, the launcher button will not be displayed in the editor.

- **Widget Launcher Location**  
  Choose where the launcher button appears in the editor.  
  Options:  
  - `MenuBar`: Shows the launcher in the main menu bar.  
  - `ToolBar`: Shows the launcher in the toolbar.  
  - `StatusBar`: Shows the launcher in the status bar.

Adjust these settings as needed to customize the behavior and appearance of the Widget Launcher.
