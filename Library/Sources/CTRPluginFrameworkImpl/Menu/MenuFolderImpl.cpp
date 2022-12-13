#include <Headers.hpp>

namespace CTRPluginFramework {
    MenuFolderImpl::MenuFolderImpl(const string &name, const string &note) :
        MenuItem(MenuType::Folder), _owner(nullptr)

        {
            this->name = name;
            this->firstName = name;
            this->note = note;
            this->_position[0] = -1;
            this->_position[1] = -1;
            this->_parent[0] = nullptr;
            this->_parent[1] = nullptr;
        }

    MenuFolderImpl::MenuFolderImpl(MenuFolder* owner, const string &name, const string &note) :
        MenuItem(MenuType::Folder), _owner(owner)

        {
            this->name = name;
            this->firstName = name;
            this->note = note;
            this->_position[0] = -1;
            this->_position[1] = -1;
            this->_parent[0] = nullptr;
            this->_parent[1] = nullptr;
        }

    MenuFolderImpl::~MenuFolderImpl() {
        for (MenuItem *item : _items) {
            // If item has an owner, call the owner's destructor
            if (item->IsEntry() && item->AsMenuEntryImpl().AsMenuEntry())
                delete item->AsMenuEntryImpl().AsMenuEntry();

            else if (item->IsFolder() && item->AsMenuFolderImpl()._owner)
                delete item->AsMenuFolderImpl()._owner;

            else delete item;
        }

        // Close this folder if it's the one opened in the menu
        PluginMenuImpl::Close(this);
        _items.clear();
    }

    void MenuFolderImpl::Append(MenuItem *item, bool isStar) {
        if (!isStar) {
            item->_container = this;
            item->_index = _items.size();
        }

        _items.push_back(item);

    }

    u32 MenuFolderImpl::ItemsCount(void) const {
        return (_items.size());
    }

    MenuItem *MenuFolderImpl::GetItem(u32 uid) {
        for (MenuItem *item : _items) {
            if (item->Uid == uid)
                return (item);

            if (item->_type == MenuType::Folder) {
                MenuItem * i = reinterpret_cast<MenuFolderImpl*>(item)->GetItem(uid);

                if (i != nullptr)
                    return (i);
            }
        }

        return (nullptr);
    }

    void MenuFolderImpl::DisableAll(void) {
        for (MenuItem *item : _items) {
            if (item->IsEntry() || item->IsFreeCheat())
                reinterpret_cast<MenuEntryImpl*>(item)->Disable();

            if (item->IsFolder())
                reinterpret_cast<MenuFolderImpl*>(item)->DisableAll();
        }
    }

    vector<MenuEntry*> MenuFolderImpl::GetEntryList(void) const {
        vector<MenuEntry*> entries;

        for (MenuItem *item : _items) {
            if (item->IsEntry()) {
                MenuEntry *entry = item->AsMenuEntryImpl().AsMenuEntry();

                if (entry != nullptr)
                    entries.push_back(entry);
            }
        }

        return (entries);
    }

    vector<MenuFolder*> MenuFolderImpl::GetFolderList(void) const {
        vector<MenuFolder*> folders;

        for (MenuItem *item : _items) {
            if (item->IsFolder()) {
                MenuFolder *folder = item->AsMenuFolderImpl()._owner;

                if (folder != nullptr)
                    folders.push_back(folder);
            }
        }

        return (folders);
    }

    MenuItem *MenuFolderImpl::operator[](u32 index) {
        if (index >= _items.size())
            return (nullptr);

        return (_items[index]);
    }

    bool MenuFolderImpl::HasParent() {
        return (_parent[0] != nullptr || _parent[1] != nullptr);
    }

    void MenuFolderImpl::Remove(MenuItem *item) {
        _items.erase(remove(_items.begin(), _items.end(), item), _items.end());
    }

    void MenuFolderImpl::Remove(u32 start, u32 count, bool destroy) {
        if (start >= _items.size())
            return;

        if (start + count >= _items.size())
            count = _items.size() - start;

        auto begin = _items.begin() + start;
        auto end = begin + count;

        if (destroy) {
            for (auto b = begin, e = end; b != e; ++b)
                delete *b;
        }

        _items.erase(begin, end);
    }

    void MenuFolderImpl::Clear(void) {
        for (MenuItem *item : _items) {
            if (item->IsEntry() && item->AsMenuEntryImpl().AsMenuEntry())
                delete item->AsMenuEntryImpl().AsMenuEntry();

            else if (item->IsFolder() && item->AsMenuFolderImpl()._owner)
                delete item->AsMenuFolderImpl()._owner;

            else delete item;
        }

        _items.clear();
    }

    void MenuFolderImpl::_Open(MenuFolderImpl *parent, int position, bool starMode) {
        int index = starMode ? 1 : 0;
        _parent[index] = parent;
        _position[index] = position;
    }

    MenuFolderImpl *MenuFolderImpl::_Close(int &position, bool starMode) {
        int index = starMode ? 1 : 0;

        if (_parent[index] != nullptr && _position[index] != -1)
            position = _position[index];

        return (_parent[index]);
    }
}