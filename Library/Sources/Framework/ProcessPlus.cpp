#include <CTRPluginFramework.hpp>
#include "Framework/Wrappers.hpp"
#include "../../../Includes/stdafx.hpp"

namespace CTRPluginFramework {
    static  u8  data8;
    static u16 data16;
    static u32 data32;

    void ProcessPlus::Write8(u32 pointer, u32 offset, u8 value) {
        u32 address;

        if (Process::Read32(pointer, address)) {
            if (Process::Read8(address + offset, data8) && data8 != value)
                Process::Write8(address + offset, value);
        }
    }

    void ProcessPlus::Write8(u32 pointer, u32 offset, u8 value, int length) {
        u32 address;

        for (int i = 0; i < length; i++) {
            if (Process::Read32(pointer + (i * 4), address)) {
                if (Process::Read8(address + offset, data8) && data8 != value)
                    Process::Write8(address + offset, value);
            }
        }
    }

    void ProcessPlus::Write16(u32 pointer, u32 offset, u16 value) {
        u32 address;

        if (Process::Read32(pointer, address)) {
            if (Process::Read16(address + offset, data16) && data16 != value)
                Process::Write16(address + offset, value);
        }
    }

    void ProcessPlus::Write16(u32 pointer, u32 offset, u16 value, int length) {
        u32 address;

        for (int i = 0; i < length; i++) {
            if (Process::Read32(pointer + (i * 4), address)) {
                if (Process::Read16(address + offset, data16) && data16 != value)
                    Process::Write16(address + offset, value);
            }
        }
    }

    void ProcessPlus::Write32(u32 pointer, u32 offset, u32 value) {
        u32 address;

        if (Process::Read32(pointer, address)) {
            if (Process::Read32(address + offset, data32) && data32 != value)
                Process::Write32(address + offset, value);
        }
    }

    void ProcessPlus::Write32(u32 pointer, u32 offset, u32 value, int length) {
        u32 address;

        for (int i = 0; i < length; i++) {
            if (Process::Read32(pointer + (i * 4), address)) {
                if (Process::Read32(address + offset, data32) && data32 != value)
                    Process::Write32(address + offset, value);
            }
        }
    }

    bool ProcessPlus::Write32(u32 address, u32 value, u32 &original, MenuEntry *entry, bool &saved) {
        if (entry->IsActivated()) {
            if (!saved) {
                original = *(u32*)address;
                saved = true;
                return true;
            }

            if (Process::Read32(address, data32) && data32 != value)
                Process::Write32(address, value);

            return true;
        }

        if (!entry->IsActivated()) {
            if (saved) {
                if (Process::Read32(address, data32) && data32 != original)
                    Process::Write32(address, original);

                original = 0;
                saved = false;
                return true;
            }
        }

        return false;
    }

    bool ProcessPlus::Write32(u32 address, vector<u32> value) {
        for (unsigned int i = 0; i < value.size(); i++) {
            if (Process::Read32(address + (i * 4), data32) && data32 != value[i]) {
                if (!Process::Write32(address + (i * 4), value[i]))
                    return false;
            }

            else return false;
        }

        return true;
    }

    void ProcessPlus::Write32(u32 address, vector<u32> value, int length) {
        for (int i = 0; i < (length / 4); i++) {
            if (Process::Read32(address + (i * 4), data32) && data32 != value[i])
                Process::Write32(address + (i * 4), value[i]);
        }
    }

    bool ProcessPlus::Write32(u32 address, vector<u32> value, vector<u32> &original, MenuEntry *entry, bool &saved) {
        if (entry->IsActivated()) {
            if (!saved) {
                for (unsigned int i = 0; i < value.size(); i++)
                    original[i] = *(u32*)(address + (i * 4));

                saved = true;
                return true;
            }

            for (unsigned int j = 0; j < value.size(); j++) {
                if (Process::Read32(address + (j * 4), data32) && data32 != value[j])
                    Process::Write32(address + (j * 4), value[j]);
            }

            return true;
        }

        if (!entry->IsActivated()) {
            if (saved) {
                ProcessPlus::Write32(address, original);
                fill(original.begin(), original.end(), 0);
                saved = false;
                return true;
            }
        }

        return false;
    }

    void ProcessPlus::Write32(vector<u32> address, vector<u32> value) {
        for (unsigned int i = 0; i < address.size(); i++) {
            if (Process::Read32(address[i], data32) && data32 != value[i])
                Process::Write32(address[i], value[i]);
        }
    }

    bool ProcessPlus::Write32(vector<u32> address, vector<u32> value, vector<u32> &original, MenuEntry *entry, bool &saved) {
        if (entry->IsActivated()) {
            if (!saved) {
                for (unsigned int i = 0; i < value.size(); i++)
                    original[i] = *(u32*)address[i];

                saved = true;
                return true;
            }

            for (unsigned int j = 0; j < address.size(); j++) {
                if (Process::Read32(address[j], data32) && data32 != value[j])
                    Process::Write32(address[j], value[j]);
            }

            return true;
        }

        if (!entry->IsActivated()) {
            if (saved) {
                ProcessPlus::Write32(address, original);
                fill(original.begin(), original.end(), 0);
                saved = false;
                return true;
            }
        }

        return false;
    }

    u8 ProcessPlus::Read8(u32 address) {
        return *(volatile unsigned char*)(address);
    }

    bool ProcessPlus::Read8(u32 address, u8 &value, bool check) {
        if (check) {
            if (!System::IsConnectedToInternet()) {
                if (Process::Read8(address, data8)) {
                    value = data8;
                    return true;
                }
            }
        }

        return false;
    }

    u16 ProcessPlus::Read16(u32 address) {
        return *(volatile unsigned short*)(address);
    }

    u32 ProcessPlus::Read32(u32 address) {
        return *(volatile unsigned int*)(address);
    }

    vector<u32> ProcessPlus::Read32(u32 address, int length) {
        vector<u32> vals(length);

        for (int i = 0; i < length; i++) {
            vals[i] = *(u32*)address;
            address += 0x4;
        }

        return vals;
    }

    string ProcessPlus::Address(string text, int s) {
        string result = "";

        for (unsigned int i = 0; i < text.length(); i++) {
            if (isupper(text[i]))
                result += char(int(text[i] + s - 65) + 65);

            else if (islower(text[i])) {
                if (int(text[i] + s) < 97)
                     result += char(123 - (97 - int(text[i] + s)));

                else result += char(int(text[i] + s - 97) + 97);
            }

            else if (isdigit(text[i])) {
                if (int(text[i] + s) < 48)
                     result += char(57 - (48 - int(text[i] + s)));

                else result += char(int(text[i] + s - 48) + 48);
            }
        }

        // Return the resulting string
        return result;
    }
}