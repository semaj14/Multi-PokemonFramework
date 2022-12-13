#include <Headers.hpp>

namespace CTRPluginFramework {
    SearchMenu::SearchMenu(Search* &curSearch, HexEditor &hexEditor, bool &inEditor, bool &useHexInput) :
        _hexEditor(hexEditor),
        _currentSearch(curSearch),
        _submenu{{"Show game"}},
        _inEditor(inEditor),
	    _useHexInput(useHexInput)

        {
            _index = 0;
            _selector = 0;
            _alreadyExported = false;
        }

    bool SearchMenu::ProcessEvent(EventList &eventList, Time &delta) {
        static Clock _fastScroll;
        static Clock _startFastScroll;
        bool isSubMenuOpen = _submenu.IsOpen();

        for (size_t i = 0; i < eventList.size(); i++) {
            Event &event = eventList[i];
            _submenu.ProcessEvent(event);

            if (isSubMenuOpen)
                continue;

            if (event.type == Event::EventType::KeyPressed && event.key.code == Key::B)
                return (true);

            // Pressed
            if (event.type == Event::EventType::KeyPressed) {
                switch (event.key.code) {
                    case Key::DPadUp: {
                        _selector = max((int)(_selector - 1),(int)(0));
                        _startFastScroll.Restart();
                        break;
                    }

                    case Key::CPadDown: {
                        _selector = min((int)(_selector + 5), (int)(_resultsAddress.size() - 1));
                        _startFastScroll.Restart();
                        break;
                    }

                    case Key::CPadUp: {
                        _selector = max((int)(_selector - 5), (int)(0));
                        _startFastScroll.Restart();
                        break;
                    }

                    case Key::DPadDown: {
                        _selector = min((int)(_selector + 1), (int)(_resultsAddress.size() - 1));
                        _startFastScroll.Restart();
                        break;
                    }

                    case Key::DPadLeft: {
                        _index = max((int)(_index + _selector - 500), (int)(0));
                        _selector = 0;
                        _startFastScroll.Restart();
                        Update();
                        break;
                    }

                    case Key::DPadRight: {
                        _index = min((int)(_index + _selector + 500),(int)(_currentSearch->ResultsCount / 500 * 500));
                        _selector = 0;
                        _startFastScroll.Restart();
                        Update();
                        break;
                    }

                    case Key::B:
                        return (true);

                    default: break;
                }
            }

            // Hold
            else if (event.type == Event::EventType::KeyDown) {
                if (_currentSearch != nullptr && _startFastScroll.HasTimePassed(Seconds(0.5f)) && _fastScroll.HasTimePassed(Seconds(0.1f))) {
                    switch (event.key.code) {
                        case Key::CPadDown: {
                            _selector = min((int)(_selector + 5), (int)(_resultsAddress.size() - 1));
                            int half = _resultsAddress.size() / 2;

                            if (_selector > half) {
                                u32 bakIndex = _index;
                                _index = min((int)(_index + half), (int)(_currentSearch->ResultsCount / 500 * 500));
                                _selector -= _index - bakIndex;
                                Update();
                            }

                            _fastScroll.Restart();
                            break;
                        }

                        case Key::CPadUp: {
                            _selector = max((int)(_selector - 5), (int)(0));
                            int half = _resultsAddress.size() / 2;

                            if (_selector < half && _index > 0) {
                                u32 bakIndex = _index;
                                _index = max((int)(_index - half), (int)(0));
                                _selector += bakIndex - _index;
                                Update();
                            }

                            _fastScroll.Restart();
                            break;
                        }

                        case Key::DPadUp: {
                            _selector = max((int)(_selector - 1),(int)(0));
                            _fastScroll.Restart();
                            break;
                        }

                        case Key::DPadDown: {
                            _selector = min((int)(_selector + 1),(int)(_resultsAddress.size() - 1));
                            _fastScroll.Restart();
                            break;
                        }

                        case Key::DPadLeft: {
                            _index = max((int)(_index + _selector - 500),(int)(0));
                            _selector = 0;
                            _fastScroll.Restart();
                            Update();
                            break;
                        }

                        case Key::DPadRight: {
                            _index = min((int)(_index + _selector + 500),(int)(_currentSearch->ResultsCount / 500 * 500));
                            _selector = 0;
                            _fastScroll.Restart();
                            Update();
                            break;
                        }

                        default: break;
                    }
                }
            }
        }

        if (_submenu.IsOpen()) {
            int subchoice = _submenu();

            if (_submenu.OptionsCount() > 4) {
                if (!subchoice--)
                    _Edit();

                else if (!subchoice--)
                    _JumpInEditor();
                else if (!subchoice--)
                    _NewCheat();
                else if (!subchoice--)
                    _Export();
                else if (!subchoice--)
                    _ExportAll();

                else if (!subchoice--) {
                    Converter *inst = Converter::Instance();

                    if (inst)
                        (*inst)();
                }
            }

            if (!subchoice--)
                _ShowGame();
        }

        return (false);
    }

    void SearchMenu::Draw(void) {
        const Color &black = Color::Black;
        const Color &blank = Color::White;
        const Color &darkgrey = Color::DarkGrey;
        const Color &gainsboro = Color::Gainsboro;
        const Color &silver = Color::Silver;
        const Color &textcolor = Preferences::Settings.MainTextColor;
        int posY = 51;

        if (_currentSearch != nullptr) {
            string str = "Step: " + to_string(_currentSearch->Step);
            Renderer::DrawString((char*)str.c_str(), 37, posY, textcolor);
            str = "Hit(s): " + to_string(_currentSearch->ResultsCount);
            Renderer::DrawString((char*)str.c_str(), 37, posY, textcolor);
        }

        posY = 80;
        Renderer::DrawRect(35, 75, 78, 20, darkgrey);
        Renderer::DrawString((char*)"Address", 53, posY, black);
        posY = 80;
        Renderer::DrawRect(113, 75, 126, 20, darkgrey);
        Renderer::DrawString((char*)"New Value", 149, posY, black);
        posY = 80;
        Renderer::DrawRect(239, 75, 126, 20, darkgrey);
        Renderer::DrawString((char*)"Old Value", 275, posY, black);
        posY = 95;

        for (int i = 0; i < 10; i++) {
            const Color &c = i % 2 ? gainsboro : blank;
            Renderer::DrawRect(35, posY, 330, 10, c);
            posY += 10;
        }

        posY = 203;
        Renderer::DrawString((char*)"Options:", 260, posY, textcolor);
        posY -= 14;
        Renderer::DrawSysString((char*)"\uE002", 320, posY, 380, textcolor);

        if (_currentSearch == nullptr || _resultsAddress.size() == 0 || _resultsNewValue.size() == 0) {
            _submenu.Draw();
            return;
        }

        posY = 95;
        int posX1 = 47;
        int posX2 = 113;
        int posX3 = 239;
        u32 start = max((int)0, (int)_selector - 5);
        u32 end = min((int)_resultsAddress.size(), (int)(start + 10));

        for (u32 i = start; i < end; i++) {
            if (i >= _resultsAddress.size())
                return;

            // Selector
            if (i == static_cast<u32>(_selector))
                Renderer::DrawRect(35, 95 + (i - start) * 10, 330, 10, silver);

            int pos = posX1;
            int posy = posY;

            // Address
            Renderer::DrawString((char*)_resultsAddress[i].c_str(), pos, posy, black);

            // newval
            posy = posY;
            string &nval = _resultsNewValue[i];
            pos = posX2 + (126 - (nval.size() * 6)) / 2;
            Renderer::DrawString((char*)nval.c_str(), pos, posy, black);

            if (i >= _resultsOldValue.size()) {
                posY += 10;
                continue;
            }

            // oldval
            string &oval = _resultsOldValue[i];
            pos = posX3 + (126 - (oval.size() * 6)) / 2;
            Renderer::DrawString((char*)oval.c_str(), pos, posY, black);
        }

        start += _index;
        string str = to_string(start) + "-" + to_string(min((u32)(start + 10), (u32)_currentSearch->ResultsCount)) + " / " + to_string(_currentSearch->ResultsCount);
        posY = 196;
        Renderer::DrawString((char*)str.c_str(), 37, posY, textcolor);
        _submenu.Draw();
    }

    void SearchMenu::Update(void) {
        _resultsAddress.clear();
        _resultsNewValue.clear();
        _resultsOldValue.clear();

        if (_currentSearch == nullptr) {
            _selector = 0;
            _index = 0;

            if (_submenu.OptionsCount() > 4)
                _submenu.ChangeOptions({"Show game"});

            return;
        }

        if (_submenu.OptionsCount() < 5 && !_currentSearch->IsFirstUnknownSearch())
            _submenu.ChangeOptions({"Edit", "Jump to Editor", "New Cheat", "Export", "Export All", "Converter", "Show Game"});

        if (_index + _selector >= _currentSearch->ResultsCount) {
            _index = 0;
            _selector = 0;
        }

        _currentSearch->ReadResults(_index, _resultsAddress, _resultsNewValue, _resultsOldValue);

        if (static_cast<size_t>(_selector) >= _resultsAddress.size())
            _selector = 0;

        // If the results are empty try again from the start of the results
        if (_resultsAddress.empty() && _currentSearch->ResultsCount > 0) {
            _index = 0;
            _selector = 0;
            Update();
        }
    }

    void SearchMenu::_OpenExportFile(void) {
        if (_export.IsOpen())
            return;

        if (File::Open(_export, "ExportedAddresses.txt", File::WRITE | File::APPEND))
            File::Open(_export, "ExportedAddresses.txt", File::WRITE | File::CREATE);
    }

    void SearchMenu::_NewCheat(void) {
        u32 address = strtoul(_resultsAddress[_selector].c_str(), NULL, 16);
        u32 value = 0;
        u8 codetype = 0;
        SearchFlags type = _currentSearch->GetType();

        if (type == SearchFlags::U8) {
            codetype = 0x20;
            u8 val8 = 0;
            Process::Read8(address, val8);
            value = val8;
        }

        else if (type == SearchFlags::U16) {
            codetype = 0x10;
            u16 val16 = 0;
            Process::Read16(address, val16);
            value = val16;
        }

        else Process::Read32(address, value);

        PluginMenuActionReplay::NewARCode(codetype, address, value);

    }

    void SearchMenu::_Edit(void) {
        Keyboard keyboard;
        keyboard.DisplayTopScreen = false;
		keyboard.IsHexadecimal(_useHexInput);
        u32 address = strtoul(_resultsAddress[_selector].c_str(), NULL, 16);

        switch (_currentSearch->GetType()) {
            case SearchFlags::U8: {
                u8 value = *(u8*)(address);
                int res = keyboard.Open(value, value);

                if (res != -1) {
                    if (Process::CheckAddress(address))
                        *(u8*)(address) = value;
                }

                break;
            }

            case SearchFlags::U16: {
                u16 value = *(u16*)(address);
                int res = keyboard.Open(value, value);

                if (res != -1) {
                    if (Process::CheckAddress(address))
                        *(u16*)(address) = value;
                }

                break;
            }

            case SearchFlags::U32: {
                u32 value = *(u32*)(address);
                int res = keyboard.Open(value, value);

                if (res != -1) {
                    if (Process::CheckAddress(address))
                        *(u32*)(address) = value;
                }

                break;
            }

            case SearchFlags::Float: {
                float value = *(float*)(address);
                int res = keyboard.Open(value, value);

                if (res != -1) {
                    if (Process::CheckAddress(address))
                        *(float*)(address) = value;
                }

                break;
            }

            default: break;
        }
    }

    void SearchMenu::_JumpInEditor(void) {
        if (!PluginMenuImpl::GetRunningInstance()->GetHexEditorState())
            return;

        u32 address = strtoul(_resultsAddress[_selector].c_str(), NULL, 16);
        _hexEditor.Goto(address, true);
        _inEditor = true;
    }

    void SearchMenu::_Export(void) {
        if (!_alreadyExported) {
            if (!_export.IsOpen())
                _OpenExportFile();

            _export.WriteLine("");
            time_t t = time(NULL);
            char *ct = ctime(&t);
            ct[strlen(ct)] = '\0';
            string text = ct;
            text += " :\r\n";
            _export.WriteLine(text);
            _alreadyExported = true;
        }

        string str = _resultsAddress[_selector] +" : " + _resultsNewValue[_selector];
        _export.WriteLine(str);
    }

    void SearchMenu::_ExportAll(void) {
        if (!_alreadyExported) {
            if (!_export.IsOpen())
                _OpenExportFile();

            _export.WriteLine("");
            _alreadyExported = true;
        }

        string out;

        for (int i = _selector; i < _selector + 10; i++) {
            if (i >= static_cast<int>(_resultsAddress.size()))
                break;

            out += _resultsAddress[i] +" : " + _resultsNewValue[i] + "\r\n";
        }

        _export.Write(out.c_str(), out.size());
    }

    void SearchMenu::_ShowGame(void) {
        MessageBox(CenterAlign("Press " FONT_B " to return to the menu."), DialogType::DialogOk, ClearScreen::Both)();
        ScreenImpl::SwitchFrameBuffers(true);

        // Clear the textbox from frame buffer
        Renderer::SetTarget(TOP);
        ScreenImpl::Top->SwapBufferInternal();
        Draw();
        ScreenImpl::Top->SwapBufferInternal();

        while (true) {
            Controller::Update();
            if (Controller::IsKeyPressed(Key::B))
                break;
        }

        ScreenImpl::SwitchFrameBuffers(false);
    }
}