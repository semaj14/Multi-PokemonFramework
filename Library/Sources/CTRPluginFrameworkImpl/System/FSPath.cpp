#include <Headers.hpp>

namespace CTRPluginFramework {
    Mutex FSPath::FSMutex;
    string FSPath::CurrentWorkingDirectory;

    int FSPath::SdmcFixPath(string &path) {
        uint32_t units;
        uint32_t code;
        string fixPath;
        const uint8_t *p = (const uint8_t*)path.c_str();
        int offset = 0;

        do {
            units = decode_utf8(&code, p);

            if (units < 0)
                return (-1);

            p += units;
            offset += units;
        }

        while (code != ':' && code != 0);

        // We found a colon; p points to the actual path
        if (code == ':')
            path = path.substr(offset);

        // Make sure there are no more colons and that the remainder of the filename is valid UTF-8
        p = (const uint8_t*)path.c_str();

        do {
            units = decode_utf8(&code, p);

            if (units < 0)
                return (-1);

            if (code == ':')
                return (-1);

            p += units;
        }

        while (code != 0);

        if (path[0] == '/')
            return (0);

        else {
            fixPath = FSPath::CurrentWorkingDirectory;
            fixPath += path;
            path = fixPath;
        }

        if (path.size() >= PATH_LENGTH_MAX)
            return (-1);

        return (0);
    }

    FSPath::FSPath(string path) {
        Lock lock(FSMutex);

        if ((Error = SdmcFixPath(path)) != 0)
            return;

        Utf16Path.resize(256, 0);
        Units = utf8_to_utf16(Utf16Path.data(), (const uint8_t*)path.c_str(), PATH_LENGTH_MAX);

        if (Units <= 0)
            Error = -1;
    }
}