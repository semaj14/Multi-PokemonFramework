#include <Headers.hpp>

namespace CTRPluginFramework {
    Menu::Menu(const string &title, const string &footer, IconCallback iconCallback) :
        _noteTB("", "", IntRect(40, 30, 320, 180))

        {
            drawFooter = false;
            _root = _folder = new MenuFolderImpl(title, footer);
            _iconCallback = iconCallback;
            _lastNoteItem = _lastSelectedItem = nullptr;
            _selector = 0;
            _reverseFlow = _selectedNameSize = 0;
            _maxScrollOffset = _scrollOffset = 0.f;
        }

    Menu::Menu(MenuFolderImpl *folder, IconCallback iconCallback) :
        _noteTB("", "", IntRect(40, 30, 320, 180))

        {
            drawFooter = false;
            _root = _folder = folder == nullptr ? new MenuFolderImpl("Menu") : folder;
            _iconCallback = iconCallback;
            _lastNoteItem = _lastSelectedItem = nullptr;
            _selector = 0;
            _reverseFlow = _selectedNameSize = 0;
            _maxScrollOffset = _scrollOffset = 0.f;
        }

    MenuFolderImpl *Menu::Open(MenuFolderImpl *folder, int selector) {
        MenuFolderImpl *f = _folder;
        _selector = max((int)0, (int)min(selector, (int)(folder->ItemsCount() - 1)));
        _folder = folder;
        return (f);
    }

    void Menu::CloseAll(void) {
        if (_root == nullptr) return;

        while (_root != _folder) {
            MenuFolderImpl *f = _folder->_Close(_selector);

            if (f == nullptr) {
                _root = _folder;
                break;
            }

            _folder = f;
        }

        _selector = 0;
    }

    Menu::~Menu(void) {
        delete _folder;
    }

    void Menu::Append(MenuItem *item) const {
        _folder->Append(item);
    }

    void Menu::Remove(MenuItem *item) {
        for (auto iter = _folder->_items.begin(); iter < _folder->_items.end(); ++iter) {
            if (*iter == item) {
                _folder->_items.erase(iter);
                break;
            }
        }

        if (_selector >= static_cast<int>(_folder->ItemsCount()))
            _selector = max((int)0, (int)(_folder->ItemsCount() - 1));
    }

    MenuFolderImpl *Menu::GetFolder(void) const {
        return (_folder);
    }

    MenuFolderImpl *Menu::GetRootFolder() const {
        return (_root);
    }

    MenuItem *Menu::GetSelectedItem() {
        int count = _folder->ItemsCount();

        if (count > 0) {
            if (_selector >= count)
                _selector = max(0, (int)count - 1);

            return (_folder->_items[_selector]);
        }

        return (nullptr);
    }

    #define XMAX 360

    void Menu::Draw(void) const {
        const Color &title = Preferences::Settings.WindowTitleColor;
        const Color &selected = Preferences::Settings.MenuSelectedItemColor;
        const Color &unselected = Preferences::Settings.MenuUnselectedItemColor;

        int posY = 25;
        int posX = 40;

        Renderer::SetTarget(TOP);
        Window::TopWindow.Draw();

        // Draw title
        Renderer::DrawSysString(_folder->name.c_str(), (400 - Renderer::GetTextSize(_folder->name.c_str())) / 2, posY, XMAX, title);
        posY += 7;

        // Draw entries
        int max = _folder->ItemsCount();
        if (max == 0) return;

        int i = std::max(0, (int)(_selector - 6));
        max = std::min(max, i + 8);

        if (_iconCallback != nullptr) {
            for (; i < max; i++) {
                const Color &c = i == _selector ? selected : unselected;
                MenuItem *item = _folder->_items[i];

                if (i == _selector)
                    Renderer::MenuSelector(posX - 5, posY - 3, 330, 20);

                if (item->_type != MenuType::Folder) {
                    _iconCallback(posX, posY);
                    Renderer::DrawSysString(item->name.c_str(), posX + 20, posY, XMAX, c);
                }

                else Renderer::DrawSysFolder(item->name.c_str(), posX, posY, XMAX, c);

                posY += 4;
            }
        }

        else {
            for (; i < max; i++) {
                const Color &c = i == _selector ? selected : unselected;
                MenuItem *item = _folder->_items[i];
                float offset = 0.f;

                if (i == _selector) {
                    offset = _scrollOffset;
                    Renderer::MenuSelector(posX - 5, posY - 3, 330, 20);
                }

                // MenuEntryImpl
                if (item->_type == MenuType::Entry)
                    Renderer::DrawSysCheckBox(item->name.c_str(), posX, posY, XMAX, c, item->AsMenuEntryImpl().IsActivated());

                else if (item->_type == MenuType::EntryTools) {
                    MenuEntryTools *e = reinterpret_cast<MenuEntryTools*>(item);

                    if (e->UseCheckBox)
                        Renderer::DrawSysCheckBox(item->name.c_str(), posX, posY, XMAX, c, e->IsActivated());

                    else {
                        if (e->Icon != nullptr)
                            e->Icon(posX, posY);

                        Renderer::DrawSysString(item->name.c_str(), posX + 20, posY, XMAX, c);
                    }
                }

                else if (item->_type == MenuType::ActionReplay)
                    Renderer::DrawSysCheckBox(item->name.c_str(), posX, posY, XMAX, c, item->AsMenuEntryImpl().IsActivated(), offset);

                // MenuFolderImpl
                else Renderer::DrawSysFolder(item->name.c_str(), posX, posY, XMAX, c);

                posY += 4;
            }
        }

        if (_noteTB.IsOpen())
            _noteTB.DrawConst();

        if (drawFooter) {
            Renderer::SetTarget(BOTTOM);
            Window::BottomWindow.Draw();

            if (!_folder->GetNote().empty()) {
                int posY = 40;
                Renderer::DrawSysStringReturn((u8*)_folder->GetNote().c_str(), 35, posY, 295, Preferences::Settings.MainTextColor, 190);
            }
        }
    }

    // Return a MenuEvent value
    int Menu::ProcessEvent(Event &event, MenuItem **userchoice) {
        if (_noteTB.IsOpen()) {
            _noteTB.ProcessEvent(event);
            return Nothing;
        }

        // If the current folder is empty
        if (_folder->ItemsCount() == 0) {
            if (event.type == Event::KeyPressed && event.key.code == Key::B) {
                MenuFolderImpl *p = _folder->_Close(_selector);

                if (p != nullptr) {
                    _folder = p;

                    if (userchoice)
                        *userchoice = reinterpret_cast<MenuItem*>(p);

                    return (MenuEvent::FolderChanged);
                }

                else return (MenuEvent::MenuClose);
            }

            return (MenuEvent::Nothing);
        }

        // Scrolling Event
        if (event.type == Event::KeyDown) {
            switch (event.key.code) {
                case CPadUp:
                case DPadUp: {
                    _ScrollUp(1);
                    return (MenuEvent::SelectorChanged);
                }

                case CPadDown:
                case DPadDown: {
                    _ScrollDown(1);
                    return (MenuEvent::SelectorChanged);
                }

                case CPadLeft:
                case DPadLeft: {
                    _ScrollUp(4);
                    return (MenuEvent::SelectorChanged);
                }

                case CPadRight:
                case DPadRight: {
                    _ScrollDown(4);
                    return (MenuEvent::SelectorChanged);
                }

                default: break;
            }
        }

        // Other event
        else if (event.type == Event::KeyPressed) {
            MenuItem *item = _folder->_items[_selector];

            if (userchoice)
                *userchoice = item;

            switch (event.key.code) {
                case A: {
                    // MenuEntryImpl
                    if (item->_type == MenuType::Entry) {
                        MenuEntryImpl &e = item->AsMenuEntryImpl();

                        if (e.IsActivated())
                            e.Disable();

                        else e.Enable();

                        return (MenuEvent::EntrySelected);
                    }

                    // MenuEntryTools
                    else if (item->_type == MenuType::EntryTools) {
                        MenuEntryTools *e = reinterpret_cast<MenuEntryTools*>(item);

                        if (e->UseCheckBox)
                            e->TriggerState();

                        if (e->Func != nullptr)
                            e->Func();

                        if (e->FuncArg != nullptr)
                            e->FuncArg(e);

                        return (MenuEvent::EntrySelected);
                    }

                    else if (item->_type == MenuType::ActionReplay) {
                        MenuEntryActionReplay *e = reinterpret_cast<MenuEntryActionReplay*>(item);
                        bool state = e->_TriggerState();

                        if (state)
                            PluginMenuExecuteLoop::AddAR(e);

                        else PluginMenuExecuteLoop::RemoveAR(e);

                        return (MenuEvent::EntrySelected);
                    }

                    // if it's a folder
                    MenuFolderImpl *folder = reinterpret_cast<MenuFolderImpl*>(item);
                    folder->_Open(_folder, _selector);
                    _folder = folder;
                    _selector = 0;
                    return (MenuEvent::FolderChanged);
                }

                case B: {
                    MenuFolderImpl *p = _folder->_Close(_selector);

                    if (p != nullptr) {
                        _folder = p;

                        if (userchoice)
                            *userchoice = reinterpret_cast<MenuItem*>(p);

                        return (MenuEvent::FolderChanged);
                    }

                    return (MenuEvent::MenuClose);

                }

                default: break;
            }
        }

        return (MenuEvent::Nothing);
    }

    void Menu::_ScrollUp(int step) {
        if (!_input.HasTimePassed(Milliseconds(200)))
            return;

        while (_selector > 0 && step-- > 0)
                _selector--;

        if (step > 0)
            _selector = max(0, static_cast<int>(_folder->ItemsCount() - 1));

        _input.Restart();
    }

    void Menu::_ScrollDown(int step) {
        if (!_input.HasTimePassed(Milliseconds(200)))
            return;

        while (_selector < static_cast<int>(_folder->ItemsCount() - 1) && step-- > 0)
            _selector++;

        if (step > 0)
            _selector = 0;

        _input.Restart();
    }

    void Menu::Update(const Time &delta) {
        // If selected item has changed, update scrolling vars
        MenuItem *item = GetSelectedItem();
        if (_lastSelectedItem != item) {
            _lastSelectedItem = item;
            _scrollOffset = 0.f;
            _reverseFlow = false;

            if (item == nullptr) {
                _selectedNameSize = 0;
                return;
            }

            float namesize = Renderer::GetTextSize(item->name.c_str());

            // If name can fit totally in the screen, no need to scroll
            if (namesize < 280.f)
                _selectedNameSize = 0;

            _selectedNameSize = static_cast<u32>(namesize);
            _maxScrollOffset = namesize - 280.f;
            _scrollClock.Restart();
            return;
        }

        // If we have nothing to scroll, just exit
        if (!_selectedNameSize || (!_reverseFlow && !_scrollClock.HasTimePassed(Seconds(2))) || (_reverseFlow && !_scrollClock.HasTimePassed(Seconds(1))))
            return;

        float deltaAsSeconds = delta.AsSeconds();

        if (deltaAsSeconds > 0.5f)
            return;

        if (!_reverseFlow) {
            if (_scrollOffset < _maxScrollOffset)
                _scrollOffset += 29.f * deltaAsSeconds;

            else {
                _reverseFlow = true;
                _scrollClock.Restart();
            }
        }

        else {
            _scrollOffset -= 55.f * deltaAsSeconds;

            if (_scrollOffset <= 0.f) {
                _reverseFlow = false;
                _scrollOffset = 0.f;
                _scrollClock.Restart();
            }
        }
    }

    bool Menu::ShowNote(void) {
        MenuItem *item = GetSelectedItem();

        if (_lastNoteItem != item) {
            _lastNoteItem = item;

            if (item == nullptr)
                return false;

            if (item->note.empty()) {
                _lastNoteItem = nullptr;
                return false;
            }

            _noteTB.Update(item->name, item->note);
        }

        if (item == nullptr)
            return false;

        _noteTB.Open();
        return true;
    }

    void Menu::CloseNote(void) {
        _noteTB.Close();
    }

    bool Menu::IsNoteOpen(void) {
        return (_noteTB.IsOpen());
    }

    void Menu::Insert(MenuItem *item) {
        if (!item || !_folder)
            return;

        if (_selector >= static_cast<int>(_folder->_items.size()))
            _folder->Append(item);

        else _folder->_items.insert(_folder->_items.begin() +_selector, item);
    }

    MenuItem *Menu::Pop(void) {
        if (!_folder->ItemsCount())
            return nullptr;

        MenuItem *ret = _folder->_items[_selector];
        _folder->_items.erase(_folder->_items.begin() + _selector);
        _ScrollUp(1);
        return ret;
    }
}