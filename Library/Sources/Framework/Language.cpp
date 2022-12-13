#include <CTRPluginFramework.hpp>
#include "Framework/Wrappers.hpp"
#include "../../../Includes/stdafx.hpp"

namespace CTRPluginFramework {
    enum Lang {
        ENG,
        FRE
    };

    // Global to keep the current language
    Lang g_language = ENG;

    string AutoLanguage(string english, string french) {
        return (g_language == ENG ? english : french);
    }
}