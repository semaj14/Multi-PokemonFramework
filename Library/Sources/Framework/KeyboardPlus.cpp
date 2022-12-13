#include <CTRPluginFramework.hpp>
#include "Framework/Wrappers.hpp"
#include "../../../Includes/stdafx.hpp"

namespace CTRPluginFramework {
    int KeyboardPlus::SetKeyboard(const string &name, bool canAbort, bool isHex, const int maxLength, u8 &output, u8 start) {
        Sleep(Milliseconds(100));
        Keyboard keyboard(name);
        keyboard.CanAbort(canAbort);
        keyboard.IsHexadecimal(isHex);
        keyboard.SetMaxLength(maxLength);
        return keyboard.Open((u8&)output, (u8)start);
    }

    int KeyboardPlus::SetKeyboard(const string &name, bool canAbort, bool isHex, const int maxLength, u16 &output, u16 start) {
        Sleep(Milliseconds(100));
        Keyboard keyboard(name);
        keyboard.CanAbort(canAbort);
        keyboard.IsHexadecimal(isHex);
        keyboard.SetMaxLength(maxLength);
        return keyboard.Open((u16&)output, (u16)start);
    }

    int KeyboardPlus::SetKeyboard(const string &name, bool canAbort, bool isHex, const int maxLength, u32 &output, u32 start) {
        Sleep(Milliseconds(100));
        Keyboard keyboard(name);
        keyboard.CanAbort(canAbort);
        keyboard.IsHexadecimal(isHex);
        keyboard.SetMaxLength(maxLength);
        return keyboard.Open((u32&)output, (u32)start);
    }

    int KeyboardPlus::SetKeyboard(const string &name, bool canAbort, const vector<string> &options, int &index) {
        Sleep(Milliseconds(100));
        Keyboard keyboard(name);
        keyboard.CanAbort(canAbort);
        keyboard.Populate(options);
        index = keyboard.Open();
        return index;
    }

    unsigned int limit[2];

    bool Callback8(const void *input, string &error) {
        u8 val = *static_cast<const u8*>(input);

        if (val >= limit[0] && val <= limit[1])
            return true;

        error = "The value must be between " << to_string(limit[0]) << "-" << to_string(limit[1]) << ".";
        return false;
    }

    bool Callback16(const void *input, string &error) {
        u16 val = *static_cast<const u16*>(input);

        if (val >= limit[0] && val <= limit[1])
            return true;

        error = "The value must be between " << to_string(limit[0]) << "-" << to_string(limit[1]) << ".";
        return false;
    }

    bool Callback32(const void *input, string &error) {
        u32 val = *static_cast<const u32*>(input);

        if (val >= limit[0] && val <= limit[1])
            return true;

        error = "The value must be between " << to_string(limit[0]) << "-" << to_string(limit[1]) << ".";
        return false;
    }
}