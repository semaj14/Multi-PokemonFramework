#include <iomanip>
#include <sstream>
#include <time.h>
#include <Headers.hpp>

namespace CTRPluginFramework {
    enum Mode {
        NORMAL = 0,
        ABOUT,
        HEXEDITOR,
        GWRAMDUMP,
        SCREENSHOT,
        MISCELLANEOUS,
        SETTINGS,
    };

    static int g_mode = NORMAL;

    PluginMenuTools::PluginMenuTools(string &about, HexEditor &hexEditor) :
        _about(about),
        _mainMenu("Tools"),
        _miscellaneousMenu("Miscellaneous"),
        _screenshotMenu("Screenshots"),
        _settingsMenu("Settings"),
        _hexEditorEntry(nullptr),
        _hexEditor(hexEditor),
        _menu(&_mainMenu, nullptr),
        _abouttb("About", _about, IntRect(30, 20, 340, 200)),
        _exit(false)

        {
            InitMenu();
        }

    static void MenuHotkeyModifier(void) {
        u32 keys = Preferences::MenuHotkeys;
        (HotkeysModifier(keys, "Select the hotkeys you'd like to use to open the menu."))();

        if (keys != 0)
            Preferences::MenuHotkeys = keys;
    }

    void PluginMenuTools::UpdateSettings(void) {
        auto item = _settingsMenu.begin() + 2;

        if (Preferences::IsEnabled(Preferences::UseFloatingBtn))
            (*item++)->AsMenuEntryTools().Enable();

        else (*item++)->AsMenuEntryTools().Disable();

        if (Preferences::IsEnabled(Preferences::AutoSaveCheats))
            (*item++)->AsMenuEntryImpl().Enable();

        else (*item++)->AsMenuEntryImpl().Disable();

        if (Preferences::IsEnabled(Preferences::AutoSaveFavorites))
            (*item++)->AsMenuEntryImpl().Enable();

        else (*item++)->AsMenuEntryImpl().Disable();

        if (Preferences::IsEnabled(Preferences::AutoLoadCheats))
            (*item++)->AsMenuEntryImpl().Enable();

        else (*item++)->AsMenuEntryImpl().Disable();

        if (Preferences::IsEnabled(Preferences::AutoLoadFavorites))
            (*item)->AsMenuEntryImpl().Enable();

        else (*item)->AsMenuEntryImpl().Disable();

        item = _miscellaneousMenu.begin();

        if (Preferences::IsEnabled(Preferences::DisplayLoadedFiles))
            (*item++)->AsMenuEntryTools().Enable();

        else (*item++)->AsMenuEntryTools().Disable();

        if (Preferences::IsEnabled(Preferences::WriteLoadedFiles))
            (*item++)->AsMenuEntryTools().Enable();

        else (*item++)->AsMenuEntryTools().Disable();

        if (Preferences::IsEnabled(Preferences::DrawTouchCursor))
            (*item++)->AsMenuEntryTools().Enable();

        else (*item++)->AsMenuEntryTools().Disable();

        if (Preferences::IsEnabled(Preferences::DrawTouchPosition))
            (*item++)->AsMenuEntryTools().Enable();

        else (*item++)->AsMenuEntryTools().Disable();
    }

    using FsTryOpenFileType = u32(*)(u32, u16*, u32);

    enum HookFilesMode {
        NONE = 0,
        OSD = 1,
        FILE = 2
    };

    static Hook g_FsTryOpenFileHook;
    static u32 g_HookMode = NONE;
    static File g_hookExportFile;
    u32 g_FsTryOpenFileAddress = 0;
    static LightLock g_OpenFileLock;

    static u32 FindNearestSTMFD(u32 addr) {
        for (u32 i = 0; i < 1024; i++) {
            addr -= 4;

            if (*(u16*)(addr + 2) == 0xE92D)
                return addr;
        }

        return (0);
    }

    static void FindFunction(u32 &FsTryOpenFile) {
        const u8 tryOpenFilePat1[] = {0x0D, 0x10, 0xA0, 0xE1, 0x00, 0xC0, 0x90, 0xE5, 0x04, 0x00, 0xA0, 0xE1, 0x3C, 0xFF, 0x2F, 0xE1};
        const u8 tryOpenFilePat2[] = {0x10, 0x10, 0x8D, 0xE2, 0x00, 0xC0, 0x90, 0xE5, 0x05, 0x00, 0xA0, 0xE1, 0x3C, 0xFF, 0x2F, 0xE1};

        u32 *addr = (u32*)0x00100000;
        u32 *maxAddress = (u32*)(Process::GetTextSize() + 0x00100000);

        while (addr < maxAddress) {
            if (!memcmp(addr, tryOpenFilePat1, sizeof(tryOpenFilePat1)) || !memcmp(addr, tryOpenFilePat2, sizeof(tryOpenFilePat2))) {
                FsTryOpenFile = FindNearestSTMFD((u32)addr);
                break;
            }

            addr++;
        }
    }

    static u32 FsTryOpenFileCallback(u32 a1, u16 *fileName, u32 mode);

    static bool InitFsTryOpenFileHook(void) {
        static bool isInitialized = false;

        if (isInitialized)
            return isInitialized;

        // Hook on OpenFile
        u32 FsTryOpenFileAddress = 0;
        FindFunction(FsTryOpenFileAddress);

        // Check that we found the function
        if (FsTryOpenFileAddress != 0) {
            // Create lock
            LightLock_Init(&g_OpenFileLock);

            // Initialize the hook
            g_FsTryOpenFileHook.InitializeForMitm(FsTryOpenFileAddress, (u32)FsTryOpenFileCallback);
            g_FsTryOpenFileAddress = FsTryOpenFileAddress;
            isInitialized = true;
        }

        else {
            OSD::Notify("Error: couldn't find OpenFile function");
            Preferences::Clear(Preferences::DisplayLoadedFiles);
        }

        return isInitialized;
    }

    static u32 FsTryOpenFileCallback(u32 a1, u16 *fileName, u32 mode) {
        u8 buffer[256] = {0};
        string str;
        int units;
        LightLock_Lock(&g_OpenFileLock);

        if (g_HookMode & OSD) {
            // Convert utf16 to utf8
            units = utf16_to_utf8(buffer, fileName, 255);

            if (units > 0) {
                str = (char*)buffer;
                OSD::Notify(str);
            }
        }

        if (g_HookMode & FILE) {
            // Convert utf16 to utf8 if necessary
            if (str.empty()) {
                units = utf16_to_utf8(buffer, fileName, 255);

                if (units > 0)
                    str = (char*)buffer;
            }

            // If string isn't empty, write to file
            if (!str.empty())
                g_hookExportFile.WriteLine(str);
        }

        LightLock_Unlock(&g_OpenFileLock);
        return HookContext::GetCurrent().OriginalFunction<u32>(a1, fileName, mode);
    }

    static void _DisplayLoadedFiles(MenuEntryTools *entry) {
        // If we must enable the hook
        if (entry->WasJustActivated()) {
            // Initialize hook
            if (!InitFsTryOpenFileHook())
                entry->Disable();

            // Enable the hook
            Preferences::Set(Preferences::DisplayLoadedFiles);
            g_HookMode |= OSD;
            g_FsTryOpenFileHook.Enable();
            return;
        }

        if (!entry->IsActivated()) {
            // Disable OSD
            Preferences::Clear(Preferences::DisplayLoadedFiles);
            g_HookMode &= ~OSD;

            // If there's no task to do on the hook, disable it
            if (g_HookMode == 0)
                g_FsTryOpenFileHook.Disable();
        }
    }

    static void _WriteLoadedFiles(MenuEntryTools *entry) {
        // If we must enable the hook
        if (entry->WasJustActivated()) {
            // Initialize hook
            if (!InitFsTryOpenFileHook())
                entry->Disable();

            // Open the file
            int mode = File::READ | File::WRITE | File::CREATE | File::APPEND;
            string filename = Utils::Format("[%016llX] - LoadedFiles.txt", Process::GetTitleID());

            if (File::Open(g_hookExportFile, filename, mode) != 0) {
                OSD::Notify(string("Error: couldn't open \"").append(filename).append("\""), Color::Red, Color::White);
                entry->Disable();
                return;
            }

            static bool firstActivation = true;

            if (firstActivation) {
                g_hookExportFile.WriteLine("\r\n\r\nNew log\r\n");
                firstActivation = false;
            }

            // Enable the hook
            g_HookMode |= FILE;
            g_FsTryOpenFileHook.Enable();
            return;
        }

        if (!entry->IsActivated()) {
            // Disable File exporting
            g_HookMode &= ~FILE;
            g_hookExportFile.Flush();
            g_hookExportFile.Close();

            // If there's no task to do on the hook, disable it
            if (g_HookMode == 0)
                g_FsTryOpenFileHook.Disable();
        }
    }

    static bool ConfirmBeforeProceed(const string &task) {
        string msg = ResetColor() << "Do you really want to " + task + "?";
        MessageBox  msgBox(CenterAlign(msg), DialogType::DialogYesNo, ClearScreen::Both);
        return (msgBox());
    }

    static void Shutdown(void) {
        if (ConfirmBeforeProceed("shutdown")) {
            srvPublishToSubscriber(0x203, 0);
            ProcessImpl::UnlockGameThreads();
            svcExitThread();
        }
    }

    static void Reboot(void) {
        if (ConfirmBeforeProceed("reboot")) {
            svcKernelSetState(7);
            svcExitThread();
        }
    }

    static MenuEntryTools *g_screenshotEntry;

    static void GetScreenShotMode(void) {
        Keyboard kb(Color::LimeGreen << "Config:\x18\n\nWhich screen(s) would you like to capture?", {"Top", "Bottom", "Both"});
        int mode = kb.Open();

        if (mode != -1)
            Screenshot::Screens = mode + 1;
    }

    string KeysToString(u32 keys);
    bool stou32(string &input, u32 &res);
    static bool g_manualScreenshotTrigger = false;

    static void Screenshot_Enabler(MenuEntryTools *entry) {
        if (!g_manualScreenshotTrigger)
            Screenshot::IsEnabled = !Screenshot::IsEnabled;
    }

    static void UpdateScreenshotText(void) {
        // Update entry
        const char *screens[3] = {"Top", "Bottom", "Both"};
        g_screenshotEntry->name = ("Screenshot: " << Color::LimeGreen).append(KeysToString(Screenshot::Hotkeys));
        g_screenshotEntry->name += "\x18, " << Color::Orange;
        g_screenshotEntry->name.append(screens[(Screenshot::Screens & SCREENSHOT_BOTH) - 1]);
        u32 time = static_cast<u32>(Screenshot::Timer.AsSeconds());

        if (time) {
            g_screenshotEntry->name += ("\x18, " << Color::DeepSkyBlue << time);
            Screenshot::Screens |= 4; ///< TIMED flags
        }

        g_manualScreenshotTrigger = true;

        if (Screenshot::IsEnabled)
            g_screenshotEntry->Enable();

        else g_screenshotEntry->Disable();

        g_manualScreenshotTrigger = false;
    }

    static void ScreenshotMenuCallback(void) {
        Keyboard kb(Color::LimeGreen << "Settings:\x18\n\nWhat do you want to change?", {"Screens", "Hotkeys", "Timer", "Name", "Directory"});
        int choice;

        do {
            choice = kb.Open();

            switch (choice) {
                ///< Screens
                case 0: {
                    GetScreenShotMode();
                    break;
                }

                ///< Hotkeys
                case 1: {
                    u32 keys = Screenshot::Hotkeys;
                    (HotkeysModifier(keys, "Select the hotkeys you'd like to use to take a new screenshot."))();

                    if (keys != 0)
                        Screenshot::Hotkeys = keys;

                    break;
                }

                ///< Timer
                case 2: {
                    u32 current = static_cast<u32>(Screenshot::Timer.AsSeconds());
                    Keyboard keyboard(Color::LimeGreen << "Timer:\x18\n\nEnter the amount of seconds you would like\nto continuously take screenshots.\n\nEnter 0 to disable the timer.\n\n" << Color::Orange << "Note that during that time, you can't\naccess the menu.");
                    keyboard.IsHexadecimal(false);
                    keyboard.OnKeyboardEvent([](Keyboard &kb, KeyboardEvent &event) {
                        if (event.type == KeyboardEvent::CharacterAdded) {
                            string &input = kb.GetInput();
                            u32 value;
                            stou32(input, value);

                            if (value > 120)
                                input = "120";
                        }
                    });

                    if (keyboard.Open(current, current) != -1)
                        Screenshot::Timer = Seconds(static_cast<float>(current));

                    break;
                }

                ///< Name
                case 3: {
                    Keyboard nameKb(Color::LimeGreen << "Name:\x18\n\nWhich name would you like for the files?");
                    string out;

                    if (nameKb.Open(out, Screenshot::Prefix) != -1)
                        Screenshot::Prefix = out;

                    break;
                }

                ///< Directory
                case 4: {
                    string out;

                    if (Utils::DirectoryPicker(out) == -1)
                        break;

                    Screenshot::Path = move(out);

                    if (Screenshot::Path[Screenshot::Path.size() - 1] != '/')
                        Screenshot::Path += '/';

                    break;
                }

                default: break;
            }
        }

        while (choice != -1);

        UpdateScreenshotText();

        // Update file count
        Screenshot::UpdateFileCount();
    }

    static void EditBacklight(MenuEntryTools *entry) {
        using LCDBacklight = Preferences::LCDBacklight;

        int userchoice;
        u16 backlight;
        ScreenImpl *screen;
        Keyboard kb;
        string triggerTop;
        string triggerBottom;
        string &message = kb.GetMessage();
        kb.DisplayTopScreen = true;

        while (true) {
            triggerTop = Preferences::Backlights[0].isEnabled ? Color::Red << "Disable for Top" : Color::LimeGreen << "Enable for Top";
            triggerBottom = Preferences::Backlights[1].isEnabled ? Color::Red << "Disable for Bottom" : Color::LimeGreen << "Enable for Bottom";

            message = "Backlight Setter\n\nSelect which screen to configure\n\n- Top screen: " + to_string(Preferences::Backlights[0].value) + ", " + (Preferences::Backlights[0].isEnabled ? (string)Color::LimeGreen + "Enabled\n" : (string)Color::Red + "Disabled\n") + ResetColor();
            message += "- Bottom screen: " + to_string(Preferences::Backlights[1].value) + ", " + (Preferences::Backlights[1].isEnabled ? (string)Color::LimeGreen + "Enabled\n" : (string)Color::Red + "Disabled\n") + ResetColor();
            message += "\n\nRemember to put the 'Auto-Brightness'\non OFF in the Home menu.";

            kb.Populate({triggerTop, "Top screen", triggerBottom, "Bottom screen"});
            userchoice = kb.Open();

            if (userchoice == -1)
                return;

            if (userchoice == 0 || userchoice == 2) {
                LCDBacklight *backlights = Preferences::Backlights;
                backlights += userchoice == 2;
                backlights->isEnabled = !backlights->isEnabled;
                continue;
            }

            screen = userchoice == 3 ? ScreenImpl::Bottom : ScreenImpl::Top;
            backlight = screen->GetBacklight();
            kb.IsHexadecimal(false);
            message = "Backlight Setter\n\nSet a value between 2 - 1023\n\nCurrent value: ";
            message += Color::LimeGreen << backlight;

            if (kb.Open(backlight, backlight) != -1) {
                backlight = max(backlight, static_cast<u16>(2));
                backlight = min(backlight, static_cast<u16>(0x3FF));
                Preferences::Backlights[userchoice == 3].value = backlight;
            }
        }
    }

    void PluginMenuTools::InitMenu(void) {
        // Main menu
        _mainMenu.Append(new MenuEntryTools("About", [] {g_mode = ABOUT;}, Icon::DrawAbout));
        _hexEditorEntry = new MenuEntryTools("HexEditor", [] {g_mode = HEXEDITOR;}, Icon::DrawGrid);
        _mainMenu.Append(_hexEditorEntry);
        _mainMenu.Append(new MenuEntryTools("Miscellaneous", nullptr, Icon::DrawMore, new u32(MISCELLANEOUS)));
        _mainMenu.Append(new MenuEntryTools("Screenshots", nullptr, Icon::DrawUnsplash, new u32(SCREENSHOT)));
        _mainMenu.Append(new MenuEntryTools("Settings", nullptr, Icon::DrawSettings, this));
        _mainMenu.Append(new MenuEntryTools("Shutdown the 3DS", Shutdown, Icon::DrawShutdown));
        _mainMenu.Append(new MenuEntryTools("Reboot the 3DS", Reboot, Icon::DrawRestart));

        // Miscellaneous menu
        _miscellaneousMenu.Append(new MenuEntryTools("Export Loaded Game Files", _WriteLoadedFiles, true));
        _miscellaneousMenu.Append(new MenuEntryTools("Display Loaded Game Files", _DisplayLoadedFiles, true));
        _miscellaneousMenu.Append(new MenuEntryTools("Display Touch Cursor", [] {Preferences::Toggle(Preferences::DrawTouchCursor);}, true, Preferences::IsEnabled(Preferences::DrawTouchCursor)));
        _miscellaneousMenu.Append(new MenuEntryTools("Display Touch Coordinates", [] {Preferences::Toggle(Preferences::DrawTouchPosition);}, true, Preferences::IsEnabled(Preferences::DrawTouchPosition)));

        // Screenshots menu
        _screenshotMenu.Append(new MenuEntryTools("Config", ScreenshotMenuCallback, Icon::DrawSettings));
        _screenshotMenu.Append((g_screenshotEntry = new MenuEntryTools("Screenshot: " << Color::LimeGreen << KeysToString(Screenshot::Hotkeys) << "\x18, " << Color::Orange << "Both screens", Screenshot_Enabler, true)));

        // Settings menu
        _settingsMenu.Append(new MenuEntryTools("Change Menu Hotkeys", MenuHotkeyModifier, Icon::DrawGameController));
        _settingsMenu.Append(new MenuEntryTools("Set Backlight (Experimental)", EditBacklight, false, false));
        _settingsMenu.Append(new MenuEntryTools("Use Floating Button", [] {Preferences::Toggle(Preferences::UseFloatingBtn);}, true, Preferences::IsEnabled(Preferences::UseFloatingBtn)));
        _settingsMenu.Append(new MenuEntryTools("Save Enabled Cheats", [] { Preferences::Toggle(Preferences::AutoSaveCheats);}, true, Preferences::IsEnabled(Preferences::AutoSaveCheats)));
        _settingsMenu.Append(new MenuEntryTools("Save Favorites", [] {Preferences::Toggle(Preferences::AutoSaveFavorites);}, true, Preferences::IsEnabled(Preferences::AutoSaveFavorites)));
        _settingsMenu.Append(new MenuEntryTools("Load Enabled Cheats at Start", [] {Preferences::Toggle(Preferences::AutoLoadCheats);}, true, Preferences::IsEnabled(Preferences::AutoLoadCheats)));
        _settingsMenu.Append(new MenuEntryTools("Load Favorites at Start", [] {Preferences::Toggle(Preferences::AutoLoadFavorites);}, true, Preferences::IsEnabled(Preferences::AutoSaveFavorites)));
    }

    bool PluginMenuTools::operator()(EventList &eventList, Time &delta) {
        if (g_mode == HEXEDITOR) {
            if (_hexEditor(eventList))
                g_mode = NORMAL;

            return (false);
        }

        if (g_mode == ABOUT) {
            if (!_abouttb.IsOpen())
                _abouttb.Open();

            else g_mode = NORMAL;
        }

        if (g_mode == GWRAMDUMP) {
            _gatewayRamDumper();
            g_mode = NORMAL;
            return (false);
        }

        // Process Event
        for (size_t i = 0; i < eventList.size(); i++)
            _ProcessEvent(eventList[i]);

        // Update
        _Update(delta);

        static Task task([](void *arg) -> s32 {
            static_cast<PluginMenuTools*>(arg)->_RenderTop();
            return 0;
        }, static_cast<void*>(this), Task::AppCores);

        task.Start();
        _RenderBottom();
        task.Wait();

        // Check buttons
        bool exit = _exit || Window::BottomWindow.MustClose();
        _exit = false;
        return (exit);
    }

    void PluginMenuTools::TriggerHexEditor(bool isEnabled) const {
        if (!isEnabled)
            _hexEditorEntry->Hide();

        else _hexEditorEntry->Show();
    }

    void PluginMenuTools::_ProcessEvent(Event &event) {
        if (_abouttb.IsOpen()) {
            _abouttb.ProcessEvent(event);
            return;
        }

        MenuItem *item = nullptr;
        static int selector = -1;
        int ret = _menu.ProcessEvent(event, &item);

        if (ret == EntrySelected && item != nullptr) {
            void *arg = ((MenuEntryTools *)item)->GetArg();

            if (arg == this) {
                selector = _menu._selector;
                _menu.Open(&_settingsMenu);
            }

            else if (arg != nullptr && *(u32*)arg == MISCELLANEOUS) {
                selector = _menu._selector;
                _menu.Open(&_miscellaneousMenu);
            }

            else if (arg != nullptr && *(u32*)arg == SCREENSHOT) {
                selector = _menu._selector;
                UpdateScreenshotText();
                _menu.Open(&_screenshotMenu);
            }
        }

        if (ret == MenuClose) {
            if (_menu.GetFolder() == &_mainMenu) {
                _exit = true;
                _menu.Open(&_mainMenu, selector);
            }

            else _menu.Open(&_mainMenu, selector);
        }
    }

    void PluginMenuTools::_RenderTopMenu(void) {}

    static const char link[] = "github.com/semaj14";

    void PluginMenuTools::_RenderTop(void) {
        // Enable renderer
        Renderer::SetTarget(TOP);

        if (_abouttb.IsOpen()) {
            _abouttb.Draw();
            return;
        }

        _menu.Draw();
    }

    string SystemModel() {
        u8 model = 0;
        std::stringstream models;

        vector<string> Model = {
            "Old 3DS",
            "Old 3DS XL",
            "New 3DS",
            "Old 2DS",
            "New 3DS XL",
            "New 2DS XL"
        };

        CFGU_GetSystemModel(&model);
        models << Model[model];
        return models.str();
    }

    string InternetAccess() {
        std::stringstream netStatus;
        netStatus << "Wi-Fi: " << (System::IsConnectedToInternet() ? "On" : "Off");
        return netStatus.str();
    }

    string CurrentTime() {
        std::ostringstream currentTime;

        time_t unixTime = time(NULL);
        struct tm* timeStruct = gmtime((const time_t*)&unixTime);

        int hours = timeStruct->tm_hour;
        int minutes = timeStruct->tm_min;
        int seconds = timeStruct->tm_sec;

        currentTime <<  "Time: " << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << minutes << ":" << std::setw(2) << seconds;

        return currentTime.str();
    }

    static const char text1[] = "Brought to you";
    static const char nextText[] = "by semaj14";

    void PluginMenuTools::_RenderBottom(void) {
        const Color &blank = Color::White;
        Renderer::SetTarget(BOTTOM);
        Window::BottomWindow.Draw();

        static Clock clock;
        static bool timesup = true;

        static const char version[] = "Version: 1.0.3";
        static const char compiled[] = "Compiled: April 7, 2023";
        const char *info[3] = {SystemModel().c_str(), InternetAccess().c_str(), CurrentTime().c_str()};

        {
            int bottom = 205;
            int posY1 = 30;
            int posY2 = 60;
            int posY3 = 80;

            if (timesup)
                Renderer::DrawString(text1, (320 - Renderer::LinuxFontSize(text1)) / 2, bottom, blank);

            else Renderer::DrawString(nextText, (320 - Renderer::LinuxFontSize(nextText)) / 2, bottom, blank);

            if (clock.HasTimePassed(Seconds(5))) {
                clock.Restart();
                timesup = !timesup;
            }

            Renderer::DrawString(version, (320 - Renderer::LinuxFontSize(version)) / 2, posY1, Color::Gray);
            Renderer::DrawString(compiled, (320 - Renderer::LinuxFontSize(compiled)) / 2, posY1, Color::Gray);

            for (unsigned int i = 0; i < sizeof(info) / sizeof(info[0]); i ++)
                Renderer::DrawString(info[i], (320 - Renderer::LinuxFontSize(info[i])) / 2, (i == 0 ? posY2 : posY3), (i == 0 ? Color::Gainsboro : Color::Gray));
        }

        Renderer::SetTarget(TOP);
        int underFrame = 225;
        Renderer::DrawString(link, 144, underFrame, Color::Black);
    }

    void PluginMenuTools::_Update(Time delta) {
        bool isTouched = Touch::IsDown();
        IntVector touchPos(Touch::GetPosition());
        Window::BottomWindow.Update(isTouched, touchPos);
    }
}