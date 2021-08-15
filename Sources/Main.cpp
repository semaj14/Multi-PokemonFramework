#include "CTRPluginFramework.hpp"
#include <3ds.h>

#include "Backgrounds/TopBackground.hpp"
#include "Backgrounds/BottomBackground.hpp"

#include "MenuXY/XY.hpp"
#include "MenuORAS/ORAS.hpp"
#include "MenuSM/SM.hpp"
#include "MenuUSUM/USUM.hpp"

namespace CTRPluginFramework
{
	// This function is called on the plugin starts (before main)
	void PatchProcess(FwkSettings &Settings)
	{
		// A compatability check right at the start
		IsCompatible();
		
		Settings.AllowActionReplay = true;
		Settings.AllowSearchEngine = true;
		
		// Customize the general interface
		Settings.MainTextColor;
		Settings.WindowTitleColor;
		Settings.MenuSelectedItemColor;
		Settings.MenuUnselectedItemColor;
		Settings.BackgroundMainColor = Color(0x14, 0x14, 0x14);
		Settings.BackgroundSecondaryColor = Color(0x14, 0x14, 0x14);
		Settings.BackgroundBorderColor;
		
		// Input keyboard customization
		Settings.Keyboard.Background = Color(0x14, 0x14, 0x14);
		Settings.Keyboard.KeyBackground = Color(0x14, 0x14, 0x14);
		Settings.Keyboard.KeyBackgroundPressed;
		Settings.Keyboard.KeyText;
		Settings.Keyboard.KeyTextPressed;
		Settings.Keyboard.Cursor;
		Settings.Keyboard.Input;
		
		// List keyboard customization
		Settings.CustomKeyboard.BackgroundMain = Color(0x14, 0x14, 0x14);
		Settings.CustomKeyboard.BackgroundSecondary = Color(0x14, 0x14, 0x14);
		Settings.CustomKeyboard.BackgroundBorder;
		Settings.CustomKeyboard.KeyBackground;
		Settings.CustomKeyboard.KeyBackgroundPressed;
		Settings.CustomKeyboard.KeyText;
		Settings.CustomKeyboard.KeyTextPressed;
		Settings.CustomKeyboard.ScrollBarBackground;
		Settings.CustomKeyboard.ScrollBarThumb;
		
		// Set built-in plugin backgrounds
		FwkSettings::SetTopScreenBackground((void*) TopBackground);
		FwkSettings::SetBottomScreenBackground((void*) BottomBackground);
	}
	
	// This function is called when the process exits. Useful to save settings, undo patchs, or clean up things
	void OnProcessExit(void);
	
	void BlankMenu(PluginMenu &Menu)
	{
		OSD::Notify(Color::Yellow << "Warning! " << Color::White << "Unsupported game version.");
	}
	
	// Main function to create menu
	int main(void)
	{
		PluginMenu *Menu = new PluginMenu(Game, 0, 1, 0, "Multi-Pokémon Framework is Pokémon plugin that is developed by Jared0714 which is based off of Nanquitas' CTRPluginFramework. This plugin is a work in progress as well as a learning exercise.\n\nWithout Nanqutas' CTRPluginFramework, this plugin wouldn't even be possible. Nonetheless, special thanks to AnalogMan151 and Hartie95 for their references and help, without them this plugin wouldn't be where it's at, and a special thanks to Kominost and Lukas for helping out with technical issues. Not to mention, old school pkmn collector1 for alpha testing, and the friendly people over on Discord for helping out. And I couldn't have done this without any of them!");
		
		// Plugin menu configurations
		Menu->ShowWelcomeMessage(false);
		Menu->SynchronizeWithFrame(true);
		Menu->SetHexEditorState(true);
		
		// Checks if the gameset is XY
		if (GamesetID == PkmnXY)
		{
			// If the version is i up-to-date (unsupported version), then use a blank menu
			if (VersionID == UnsupportedVer)
				BlankMenu(*Menu);
			
			// Otherwise, initiate the regular menu
			else XY::Menu(*Menu);
		}
		
		// Checks if the gameset is ORAS
		if (GamesetID == PkmnORAS)
		{
			// If the version is i up-to-date (unsupported version), then use a blank menu
			if (VersionID == UnsupportedVer)
				BlankMenu(*Menu);
			
			// Otherwise, initiate the regular menu
			else ORAS::Menu(*Menu);
		}
		
		// Checks if the gameset is SM
		if (GamesetID == PkmnSM)
		{
			// If the version is i up-to-date (unsupported version), then use a blank menu
			if (VersionID == UnsupportedVer)
				BlankMenu(*Menu);
			
			// Otherwise, initiate the regular menu
			else SM::Menu(*Menu);
		}
		
		// Checks if the gameset is USUM
		if (GamesetID == PkmnUSUM)
		{
			// If the version is i up-to-date (unsupported version), then use a blank menu
			if (VersionID == UnsupportedVer)
				BlankMenu(*Menu);
			
			// Otherwise, initiate the regular menu
			else USUM::Menu(*Menu);
		}
		
		// Launch the menu and main loop
		Menu->Run();
		
		// Exits the plugin
		delete Menu;
		return (0);
	}
}
