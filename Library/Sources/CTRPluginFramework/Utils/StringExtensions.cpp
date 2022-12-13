#include <Headers.hpp>

namespace CTRPluginFramework {
    string ResetColor(void) {
        return ("\x18");
    }

    string ToggleDrawMode(u32 flags) {
        char code[4];
        code[0] = '\x11';
        *(u16*)&code[1] = 0x4080 | (flags & 0x7F);
        code[3] = '\0';
        return (code);
    }

    string SkipToPixel(u16 px) {
        char code[4];

        if (px == 0)
            code[0] = '\0';

        else {
            code[0] = '\x11';
            *(u16*)&code[1] = 0x8000 | (px & 0x1FF);
            code[3] = '\0';
        }

        return (code);
    }

    static size_t SafeStringHalve(const string &str) {
        size_t middle = str.length()/2;
        const char* strC = str.c_str();

        for (u32 i = 0; i < 4 && middle >= i; i++) {
            char c = strC[middle - i];

            if (c == 0x11 || c == 0x1B) { // Special characters, cannot cut, max length special character is 4.
                middle = middle - i;
                i = 0;

                if (middle == 0)
                    break;
            }
        }

        return middle;
    }

    static string CenterAlignImpl(const string &str, u16 leftBorder, u16 rightBorder, int rec) {
        if (rec >= 10) // Hacky and lazy way to prevent infinite recursion.
            return "";

        string line;
        string out;
        StringLineReader reader(str);

        while(reader(line)) {
            u32 size = (u32)Render::GetTextWidth(line);

            if (size > (u32)rightBorder - (u32)leftBorder) {
                size_t middle = SafeStringHalve(line);
                string left = line.substr(0, middle);
                string right = line.substr(middle);
                out += CenterAlignImpl(left, leftBorder, rightBorder, rec+1) + "\n" + CenterAlignImpl(right, leftBorder, rightBorder, rec+1) + "\n";
            }

            else {
                u16 offset = (((rightBorder - leftBorder) - size) / 2) + leftBorder;
                out += SkipToPixel(offset) + line + "\n";
            }
        }

        if (!out.empty() && !str.empty() && str[str.length() -1] != '\n')
            out.pop_back(); // Remove last \n

        return out;
    }

    string CenterAlign(const string &str, u16 leftBorder, u16 rightBorder) {
        return CenterAlignImpl(str, leftBorder, rightBorder, 0);
    }

    string RightAlignImpl(const string &str, u16 leftBorder, u16 rightBorder, int rec) {
        if (rec >= 10) // Hacky and lazy way to prevent infinite recursion.
            return "";

        string line;
        string out;
        StringLineReader reader(str);

        while(reader(line)) {
            u32 size = (u32)Render::GetTextWidth(line);

            if ((size + 1) > (u32)rightBorder - (u32)leftBorder) {
                size_t middle = SafeStringHalve(line);
                string left = line.substr(0, middle);
                string right = line.substr(middle);
                out += RightAlignImpl(left, leftBorder, rightBorder, rec+1) + "\n" + RightAlignImpl(right, leftBorder, rightBorder, rec+1) + "\n";
            }

            else {
                u16 offset = rightBorder - (size + 1);
                out += SkipToPixel(offset) + line + "\n";
            }
        }

        if (!out.empty() && !str.empty() && str[str.length() -1] != '\n')
            out.pop_back(); // Remove last \n

        return out;
    }

    string RightAlign(const string &str, u16 leftBorder, u16 rightBorder) {
        return RightAlignImpl(str, leftBorder, rightBorder, 0);
    }

    string HorizontalSeparator() {
        return "\n" << ToggleDrawMode(Render::FontDrawMode::STRIKETHROUGH) << " " << RightAlign(" ", 35, 366) << ToggleDrawMode(Render::FontDrawMode::STRIKETHROUGH) << "\n";
    }

    string operator<<(const string &left, const char* right) {
        return (left + right);
    }

    string operator <<(const string &left, const string &right) {
        return (left + right);
    }
}