#include <CTRPluginFramework.hpp>
#include "Framework/Wrappers.hpp"
#include "../../../Includes/stdafx.hpp"

namespace CTRPluginFramework {
    MenuEntry *EntryWithHotkey(MenuEntry *entry, const Hotkey &hotkey) {
        if (entry != nullptr)
            entry->Hotkeys += hotkey;

        return (entry);
    }

    MenuEntry *EntryWithHotkey(MenuEntry *entry, const vector<Hotkey> &hotkeys) {
        if (entry != nullptr) {
            for (const Hotkey &hotkey : hotkeys)
                entry->Hotkeys += hotkey;
        }

        return (entry);
    }
}