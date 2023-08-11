#ifndef LANGUAGE_HPP
#define LANGUAGE_HPP

#include <CTRPluginFramework.hpp>
#include "../../../Includes/stdafx.hpp"

#include "../CTRPluginFramework/System/Process.hpp"
#include "../CTRPluginFrameworkImpl/System/ProcessImpl.hpp"

namespace CTRPluginFramework {
    // Define an enumeration for supported languages
    enum Lang {
        ENG, // English
        FRE,  // French
        ITA  // Italiano
    };
}

#endif