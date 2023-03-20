#include <CTRPluginFramework.hpp>
#include "Framework/Wrappers.hpp"
#include "../../../Includes/stdafx.hpp"

namespace CTRPluginFramework {
    // Define an enumeration for supported languages
    enum Lang {
        ENG, // English
        FRE  // French
    };

    // Language class to manage the current language setting and provide translation functionality
    class Language {
        public:
            // Constructor to initialize the current language to English by default
            Language() : m_currentLanguage(ENG) {}

            // Function to set the current language
            void setLanguage(Lang lang) {
                m_currentLanguage = lang;
            }

            // Function to get the current language
            Lang getLanguage() const {
                return m_currentLanguage;
            }

            // Function to automatically choose the correct translation based on the current language setting
            string autoLanguage(string english, string french) const {
                return (m_currentLanguage == ENG ? english : french);
            }

        private:
            Lang m_currentLanguage; // Member variable to store the current language setting
    };
}