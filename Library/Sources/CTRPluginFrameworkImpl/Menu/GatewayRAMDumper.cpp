#include <Headers.hpp>

namespace CTRPluginFramework {
    GatewayRAMDumper::GatewayRAMDumper(void) :
        _currentAddress(0),
        _endAddress(0),
        _regionIndex(0),
        _achievedSize(0),
        _totalSize(0)
    {}

    static volatile bool g_progressLoop;

    bool GatewayRAMDumper::operator()(void) {
        // Clear variables
        _fileName.clear();
        _file.Seek(0, File::SET);
        _currentAddress = 0;
        _endAddress = 0;
        _regionIndex = 0;
        _achievedSize = 0;
        _totalSize = 0;

        // Allocate buffer
        u32 size = min((u32)((u32)Heap::SpaceFree() & ~0xFFF), (u32)0x60000);
        void *buffer = nullptr;

        if (size)
            buffer = Heap::Alloc(size);

        if (!buffer) {
            (MessageBox(CenterAlign("An error occured (buffer alloc failed)"), DialogType::DialogOk, ClearScreen::Both))();
            return (true);
        }

        // Get regions list
        PluginMenuImpl::GetRegionsList(_regions);

        if (_SelectRegion()) {
            Heap::Free(buffer);
            return (true);
        }

        _OpenFile();

        // Check that the file is opened
        if (!_file.IsOpen())
            return (true);

        _WriteHeader();

        Task progressTask([](void *arg) -> s32 {
            do reinterpret_cast<GatewayRAMDumper*>(arg)->_DrawProgress();
            while (g_progressLoop);

            return 0;
        }, this, Task::AppCores);

        g_progressLoop = true;
        progressTask.Start();

        for (Region &region : _regions) {
            // Set variables
            _currentAddress = region.startAddress;
            _endAddress = region.endAddress;
            u8 *_pool = static_cast<u8*>(buffer);

            // Dump region in chunk
            while (_currentAddress < _endAddress) {
                u8 *pool = _pool;
                u32 *pool32 =reinterpret_cast<u32*>(_pool);
                u32 size = _endAddress - _currentAddress;
                size = size > 0x60000 ? 0x60000 : size;
                u32 ssize = size;

                // Copy memory to pool
                while (ssize >= 4) {
                    *pool32++ = *reinterpret_cast<u32*>(_currentAddress);
                    _currentAddress += 4;
                    ssize -= 4;
                }

                pool = reinterpret_cast<u8*>(pool32);

                while (ssize-- > 0)
                    *pool++ = *reinterpret_cast<u8*>(_currentAddress++);

                _achievedSize += size;
                _file.Write(_pool, size);
                Controller::Update();

                if (Controller::IsKeyPressed(B)) {
                    g_progressLoop = false;
                    progressTask.Wait();
                    goto abort;
                }
            }
        }

        // Wait for task to end
        g_progressLoop = false;
        progressTask.Wait();

        // A little message
        MessageBox(CenterAlign("Dump finished!"), DialogType::DialogOk, ClearScreen::Both)();
        _file.Flush();
        _file.Close();
        Heap::Free(buffer);
        return (true);

        abort:
        _file.Close();
        Heap::Free(buffer);
        string path("Dumps/" + _fileName);
        File::Remove(path);
        Heap::Free(buffer);
        return (true);
    }

    static u32 HowManyAreSelected(MenuFolderImpl &folder) {
        u32 count = 0;

        for (u32 i = 0; i < folder.ItemsCount(); i++) {
            if (folder[i]->AsMenuEntryImpl().IsActivated())
                count++;
        }

        return (count);
    }

    bool GatewayRAMDumper::_SelectRegion(void) {
        Menu menu("Dumper", "Select the region(s) to dump.\n\nKey:\n    " FONT_A ": (De)Select the current region\n    Select: (De)Select all regions\n    Start: Start the dump");
        Event event;
        EventManager manager(EventManager::EventGroups::GROUP_KEYS);
        bool exit = false;
        bool select = false;
        menu.drawFooter = true;

        // Construct our menu with the regions list
        for (Region &region : _regions) {
            string &&name = Utils::Format("%08X to %08X", region.startAddress, region.endAddress);
            menu.Append(new MenuEntryImpl(name));
        }

        again:
        do {
            while (manager.PollEvent(event) && !exit) {
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Key::Start)
                        exit = true;

                    else if (event.key.code == Key::Select) {
                        MenuFolderImpl &folder = *menu.GetFolder();

                        if (!select) {
                            for (u32 i = 0; i < folder.ItemsCount(); i++)
                                folder[i]->AsMenuEntryImpl().Enable();
                        }

                        else {
                            for (u32 i = 0; i < folder.ItemsCount(); i++)
                                folder[i]->AsMenuEntryImpl().Disable();
                        }

                        select = !select;
                    }
                }

                exit |= menu.ProcessEvent(event, nullptr) == MenuEvent::MenuClose;
            }

            menu.Draw();
            Renderer::EndFrame();
        }

        while (!exit);

        if (HowManyAreSelected(*menu.GetFolder()) == 0) {
            exit = false;

            if (!(MessageBox(CenterAlign("Would you like to abort dumping?"), DialogType::DialogYesNo, ClearScreen::Both)()))
                goto again;

            return (true);
        }

        // Remove every entry not checked from the regions list
        MenuFolderImpl &folder = *menu.GetFolder();

        for (int i = folder.ItemsCount() - 1; i >= 0; i--) {
            if (!folder[i]->AsMenuEntryImpl().IsActivated())
                _regions.erase(_regions.begin() + i);
        }

        return (false);
    }

    void GatewayRAMDumper::_OpenFile(void) {
        char buffer[100] = {0};
        time_t t = time(NULL);
        struct tm *timeinfo = localtime(&t);
        strftime(buffer, 100, "%x-%X", timeinfo);
        string timeString(buffer);
        timeString.erase(remove(timeString.begin(), timeString.end(), '/'), timeString.end());
        timeString.erase(remove(timeString.begin(), timeString.end(), ':'), timeString.end());
        MessageBox msgBox(CenterAlign("Do you want to name the file?"), DialogType::DialogYesNo, ClearScreen::Both);

        if (msgBox()) {
            Keyboard keyboard;
            keyboard.DisplayTopScreen = false;

            if (keyboard.Open(_fileName) == -1)
                return;
        }

        else Process::GetTitleID(_fileName);

        _fileName += "-";
        _fileName += timeString + ".bin";
        string path("Dumps");

        // Create Dump directory if doesn't exists
        if (!Directory::IsExists(path))
            Directory::Create(path);

        // Assemble path
        path += "/";
        path += _fileName;

        // Open file
        if (File::Open(_file, path, File::READ | File::WRITE | File::CREATE))
            MessageBox(CenterAlign("Error\n\nCouldn't create: \n" + path), DialogType::DialogOk, ClearScreen::Both)();
    }

    #define REGION_INFOS_LENGTH (sizeof(u32) * 3)

    void GatewayRAMDumper::_WriteHeader(void) {
        u32 p_buffer[0x100];
        u32 *buffer = p_buffer;
        u32 fileOffset = sizeof(u32) * 2 + REGION_INFOS_LENGTH * _regions.size();
        *buffer++ = _regions.size();
        *buffer++ = 0;

        // Wrtie region's infos
        for (Region &region : _regions) {
            u32 regionSize = region.endAddress - region.startAddress;
            *buffer++ = region.startAddress;
            *buffer++ = fileOffset;
            *buffer++ = regionSize;
            fileOffset += regionSize;
            _totalSize += regionSize;

            // Flush region
            svcFlushProcessDataCache(ProcessImpl::ProcessHandle, region.startAddress, regionSize);
        }

        // Buffer to file
        _file.Write(p_buffer, (u32)buffer - (u32)p_buffer);
    }

    void GatewayRAMDumper::_DrawProgress() {
        const Color &gainsboro = Color::Gainsboro;
        const Color &limegreen = Color::LimeGreen;
        static ProcessingLogo logo;
        Renderer::SetTarget(TOP);
        Window::TopWindow.Draw("Gateway RAM Dumper");
        int posY = 116;
        logo.Draw(192, posY - 16);
        IntRect progBarBorder = IntRect(100, posY, 200, 15);
        Renderer::DrawRect(progBarBorder, gainsboro, false);
        float percent = 198.f / 100.f;
        float progress = 100.0f * (float)(_achievedSize) / (float)_totalSize;
        float prog = progress * percent;
        IntRect progBarFill = IntRect(101, posY + 1, (u32)prog, 13);
        Renderer::DrawRect(progBarFill, limegreen);
        Renderer::SetTarget(BOTTOM);
        Window::BottomWindow.Draw();
        Renderer::EndFrame();
    }
}