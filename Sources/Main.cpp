#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Menu.hpp"

namespace CTRPluginFramework {
    void InitLang(void) {
        File file(path + "/Lang.txt");
        string language;

        if (File::Exists(path + "/Lang.txt") == 0)
            File::Create(path + "/Lang.txt");

        if (File::Exists(path + "/Lang.txt") == 1) {
            LineReader readFile(file);
            readFile(language);

            if (language == "English")
                currLang = Lang::ENG;

            if (language == "Francais")
                currLang = Lang::FRE;
        }

        else return;
    }

    void PatchProcess(FwkSettings &settings) {
        IsCompatible();
        InitLang();

        settings.AllowActionReplay = true;
        settings.AllowSearchEngine = true;

        settings.MainTextColor = Color::White;
        settings.WindowTitleColor = Color::White;
        settings.MenuSelectedItemColor = Color::White;
        settings.MenuUnselectedItemColor = Color::Silver;

        settings.BackgroundMainColor;
        settings.BackgroundSecondaryColor;

        settings.BackgroundBorderColor = Color::White;
        settings.CursorFadeValue = -0.2f;

        settings.Keyboard.Background = Color::BlackGrey;
        settings.Keyboard.KeyBackground = Color::BlackGrey;
        settings.Keyboard.KeyBackgroundPressed = Color::Silver;
        settings.Keyboard.KeyText = Color::White;
        settings.Keyboard.KeyTextPressed = Color::Black;
        settings.Keyboard.KeyTextDisabled = Color::DimGrey;
        settings.Keyboard.Cursor = Color::Silver;
        settings.Keyboard.Input = Color::White;

        settings.CustomKeyboard.BackgroundMain = Color::BlackGrey;
        settings.CustomKeyboard.BackgroundSecondary = Color::BlackGrey;
        settings.CustomKeyboard.BackgroundBorder = Color::Silver;
        settings.CustomKeyboard.KeyBackground = Color(51, 51, 51);
        settings.CustomKeyboard.KeyBackgroundPressed = Color::Gainsboro;
        settings.CustomKeyboard.KeyText = Color::White;
        settings.CustomKeyboard.KeyTextPressed = Color::Black;
        settings.CustomKeyboard.ScrollBarBackground = Color::Silver;
        settings.CustomKeyboard.ScrollBarThumb = Color::DimGrey;
    }

    bool Loaded(void) {
        if (Process::Read32(Helpers::AutoRegion(Helpers::GetVersion(0x8C61830, 0x8C68E30), Helpers::GetVersion(0x33160BFC, 0x3309E54C)), data32) && data32 == Helpers::AutoRegion<u32>(Helpers::GetVersion(0x81820F0, 0x81873F0), Helpers::GetVersion<u32>(0x7DC147C0, Helpers::PickGame<u32>(0x90BB9C40, 0x90BB97D0))))
            return true;

        return false;
    }

    int main(void) {
        PluginMenu *menu = new PluginMenu("Multi-Pokémon Framework", 1, 0, 0, "Multi-Pokémon Framework is a plugin developed by semaj14 that uses the CTRPluginFramework library by The Pixellizer Group.\n\nThis plugin is a work in progress as well as a learning exercise.\n\nFor more info, visit the official GitHub page.");
        menu->ShowWelcomeMessage(false);
        menu->SynchronizeWithFrame(true);
        menu->SetHexEditorState(true);
        Sleep(Seconds(1));

        if (game == Game::None || group == Group::None)
            Process::ReturnToHomeMenu();

        Idle:
        Sleep(Seconds(1));

        if (Loaded())
            Sleep(Seconds(0));

        else goto Idle;

        if (game != Game::None && update == Update::Supported) {
            Sleep(Seconds(3));
            OSD::Notify("Welcome!");
            InitMenu(*menu);
        }

        menu->Callback(Helpers::MenuCallback);
        menu->Run();
        delete menu;
        return (0);
    }
}