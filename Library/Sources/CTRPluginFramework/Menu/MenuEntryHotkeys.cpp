#include <Headers.hpp>

namespace CTRPluginFramework {
    Hotkey::Hotkey() :
        _keys(0)
    {}

    Hotkey::Hotkey(u32 keys, const string &name) :
        _keys(keys), _name(name)
    {}

    Hotkey::~Hotkey() {}

    void Hotkey::operator = (u32 keys) {
        _keys = keys;
    }

    void Hotkey::operator = (const string &name) {
        _name = name;
    }

    bool Hotkey::IsDown(void) const {
        return (Controller::IsKeysDown(_keys));
    }

    bool Hotkey::IsPressed(void) const {
        return (Controller::IsKeysPressed(_keys));
    }

    void Hotkey::AskForKeys(void) {
        HotkeysModifier(_keys, "Select the keys below you want to use from below:")();
    }

    u32 Hotkey::GetKeys(void) {
        return (_keys);
    }

    const string &Hotkey::GetName() const {
        return _name;
    }

    static const string g_keyName[16] = {
        FONT_A,
        FONT_B,
        "Select",
        "Start",
        FONT_DR,
        FONT_DL,
        FONT_DU,
        FONT_DD,
        FONT_R,
        FONT_L,
        FONT_X,
        FONT_Y,
        "",
        "",
        FONT_ZL,
        FONT_ZR
    };

    string KeysToString(u32 keys) {
        string ret;
        bool add = false;

        for (int i = 0; i < 16; i++) {
            if (keys & (1u << i)) {
                if (add)
                    ret += " + ";

                ret += g_keyName[i];
                add = true;
            }
        }

        return (ret);
    }

    string Hotkey::ToString(bool withName) const {
        if (withName)
            return (_name + ": " + KeysToString(_keys));

        return (KeysToString(_keys));
    }

    HotkeyManager::HotkeyManager(MenuEntry *owner) :
        _owner(owner),
        _callback(nullptr)
    {}

    HotkeyManager::~HotkeyManager() {}

    void HotkeyManager::operator += (const Hotkey &hotkey) {
        _hotkeys.push_back(hotkey);
    }

    static Hotkey g_dummy = Hotkey(0, "Dummy");

    Hotkey &HotkeyManager::operator[](u32 index) {
        if (index >= _hotkeys.size())
            return (g_dummy);

        return (_hotkeys[index]);
    }

    Hotkey &HotkeyManager::operator[](const string &name) {
        for (auto& hk : _hotkeys) {
            if (hk._name == name)
                return hk;
        }

        return (g_dummy);
    }

    string HotkeyManager::ToString(void) {
        if (_hotkeys.size() == 0)
            return ("");

        string ret("Hotkeys:\n");

        for (Hotkey &hotkey : _hotkeys)
            ret += hotkey.ToString(true) + "\n";

        return (ret);
    }

    void HotkeyManager::AskForKeys(void) {
        if (_hotkeys.size() == 0)
            return;

        Keyboard keyboard("Hotkeys Modifier:\n\nWhich hotkey do you want to change ?");
        vector<string> hkNames;
        int ret;

        for (Hotkey &hotkey : _hotkeys)
            hkNames.push_back(hotkey._name);

        keyboard.Populate(hkNames);

        do {
            ret = keyboard.Open();

            if (ret != -1) {
                _hotkeys[ret].AskForKeys();

                if (_callback != nullptr)
                    _callback(_owner, ret);

                _owner->RefreshNote();
            }

        }

        while (ret != -1);
    }

    void HotkeyManager::OnHotkeyChangeCallback(OnHotkeyChangeClbk callback) {
        _callback = callback;
    }

    u32 HotkeyManager::Count(void) {
        return (_hotkeys.size());
    }
}