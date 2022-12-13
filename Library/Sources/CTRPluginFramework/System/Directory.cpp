#include <Headers.hpp>

namespace CTRPluginFramework {
    extern FS_Archive _sdmcArchive;

    int Directory::ChangeWorkingDirectory(const string &path) {
        FSPath fspath(path);

        if (fspath.Error)
            return INVALID_PATH;

        Lock lock(FSPath::FSMutex);
        FSPath::CurrentWorkingDirectory = path;

        if (path[path.size() - 1] != '/')
            FSPath::CurrentWorkingDirectory += '/';

        return SUCCESS;
    }

    int Directory::Create(const string &path) {
        FSPath  fsPath(path);

        if (fsPath.Error)
            return (INVALID_PATH);

        Result res;
        res = FSUSER_CreateDirectory(_sdmcArchive, fsPath, 0);

        if (res == static_cast<Result>(0xC82044BE) || R_SUCCEEDED(res))
            return (SUCCESS);

        return (res);
    }

    int Directory::Remove(const string &path) {
        // Don't recursively delete root !
        if (path == "/")
            return INVALID_PATH;

        FSPath fsPath(path);

        if (fsPath.Error)
            return (INVALID_PATH);

        Result res;
        res = FSUSER_DeleteDirectoryRecursively(_sdmcArchive, fsPath);

        if (R_SUCCEEDED(res))
            return (SUCCESS);

        return (res);
    }

    int Directory::Rename(const string &oldPath, const string &newPath) {
        FSPath fsOldPath(oldPath);
        FSPath fsNewPath(newPath);

        if (fsNewPath.Error || fsOldPath.Error)
            return (INVALID_PATH);

        Result res;
        res = FSUSER_RenameDirectory(_sdmcArchive, fsOldPath, _sdmcArchive, fsNewPath);

        if (R_SUCCEEDED(res))
            return (SUCCESS);

        return (res);
    }

    int Directory::IsExists(const string &path) {
        FSPath fsPath(path);

        if (fsPath.Error)
            return (INVALID_PATH);

        Result res;
        Handle handle;
        res = FSUSER_OpenDirectory(&handle, _sdmcArchive, fsPath);

        if (R_SUCCEEDED(res)) {
            FSDIR_Close(handle);
            return (1);
        }

        return (0);
    }

    int Directory::Open(Directory &output, const string &path, bool create) {
        Lock lock(output._mutex);

        if (output._isOpen)
            output.Close();

        output._path.clear();
        output._handle = 0;
        output._isOpen = false;
        output._list.clear();
        FSPath fsPath(path);

        if (fsPath.Error)
            return (INVALID_PATH);

        Result res;
        Handle handle;
        res = FSUSER_OpenDirectory(&handle, _sdmcArchive, fsPath);

        if (R_FAILED(res)) {
            if (create) {
                if ((res = Create(path)) != 0)
                    return (res);

                res = FSUSER_OpenDirectory(&handle, _sdmcArchive, fsPath);

                if (R_FAILED(res))
                    return (res);
            }

            else return (res);
        }

        output._path = path;
        FSPath::SdmcFixPath(output._path);
        output._handle = handle;
        output._isOpen = true;
        return (res);
    }

    int Directory::Close(void) const {
        Lock lock(_mutex);

        if (!_isOpen)
            return (NOT_OPEN);

        Result res;
        res = FSDIR_Close(_handle);

        if (R_SUCCEEDED(res)) {
            _isOpen = false;
            return (SUCCESS);
        }

        return (res);
    }

    int Directory::OpenFile(File &output, const string &path, int mode) const {
        if (!_isOpen)
            return (NOT_OPEN);

        string fullPath;

        if (path[0] != '/')
            fullPath = _path + "/" + path;

        else fullPath = _path + path;

        return (File::Open(output, fullPath, mode));
    }

    int Directory::_List(void) const {
        Lock _lock(_mutex);
        FS_DirectoryEntry *entry = (FS_DirectoryEntry*)Heap::Alloc(sizeof(FS_DirectoryEntry) * 100);
        u32 entriesNb = 0;
        u8 filename[PATH_LENGTH_MAX];
        int units;

        if (entry != nullptr)
            while (R_SUCCEEDED(FSDIR_Read(_handle, &entriesNb, 100, entry))) {
                if (entriesNb == 0)
                    break;

                for (u32 i = 0; i < entriesNb; ++i) {
                    // Convert name from utf16 to utf8
                    units = utf16_to_utf8(filename, entry[i].name, PATH_LENGTH_MAX - 1);

                    if (units == -1)
                        continue;

                    filename[units] = 0;
                    _list.push_back(DirectoryEntry(entry[i].attributes, filename));
                }
            }

        if (entry == nullptr || _list.empty()) {
            Heap::Free(entry);
            return (-1);
        }

        // Sort the file list
        sort(_list.begin(), _list.end(), [](const DirectoryEntry &lhs, const DirectoryEntry &rhs ) {
            u8 *left = (u8*)lhs.name.c_str();
            u8 *right = (u8*)rhs.name.c_str();
            u32 leftCode;
            u32 rightCode;

            do {
                ssize_t leftUnits = decode_utf8(&leftCode, left);
                ssize_t rightUnits = decode_utf8(&rightCode, right);

                if (leftUnits == -1 || rightUnits == -1)
                    break;

                left += leftUnits;
                right += rightUnits;
            }

            while (leftCode == rightCode && leftCode != 0 && rightCode != 0);

            return (leftCode < rightCode);
        });

        Heap::Free(entry);
        return (0);
    }

    Directory::DirectoryEntry::DirectoryEntry(u32 attrib, u8 *fname) :
        attributes{attrib},
        name{reinterpret_cast<char*>(fname)}
    {}

    int Directory::ListFiles(vector<string> &files, const string &pattern) const {
        Lock _lock(_mutex);

        if (!_isOpen)
            return (NOT_OPEN);

        const bool patternCheck = !pattern.empty();

        if (_list.empty())
            _List();

        int count = files.size();

        for (DirectoryEntry &entry : _list) {
            // If entry is a folder, continue
            if (entry.attributes & 1)
                continue;

            string &fn = entry.name;

            if (patternCheck && fn.find(pattern) == string::npos)
                continue;

            files.push_back(fn);
        }

        return (files.size() - count);
    }

    int Directory::ListDirectories(vector<string> &folders, const string &pattern) const {
        Lock lock(_mutex);

        if (!_isOpen)
            return (NOT_OPEN);

        const bool patternCheck = !pattern.empty();

        if (_list.empty())
            _List();

        int count = folders.size();

        for (DirectoryEntry &entry : _list) {
            // If entry is a file, continue
            if (!(entry.attributes & 1))
                continue;

            string &fn = entry.name;

            if (patternCheck && fn.find(pattern) == string::npos)
                continue;

            folders.push_back(fn);
        }

        return (folders.size() - count);
    }

    string Directory::GetName(void) const {
        size_t pos = _path.rfind("/");

        if (pos != string::npos)
            return (_path.substr(pos + 1));

        return (_path); ///< Better return path than nothing
    }

    string Directory::GetFullName(void) const {
        return (_path);
    }

    bool Directory::IsOpen(void) const {
        return (_isOpen);
    }

    Directory::Directory(void) :
        _handle(0),
        _isOpen(false)
    {}

    Directory::Directory(const string &path, bool create) :
        _handle(0),
        _isOpen(false)

        {
            Open(*this, path, create);
        }

    Directory::~Directory() {
        _list.clear();
        Close();
    }
}