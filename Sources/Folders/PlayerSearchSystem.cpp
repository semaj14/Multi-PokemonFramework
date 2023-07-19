#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

namespace PSS {
    namespace GlobalTradeStation {
        struct Deposit {
            const char *name;
            int val1;
            int val2;
        };

        namespace English {
            static const Deposit deposit[7] = {
                {"Back", 0x45, 0x40},
                {"Quit the GTS", 0x4F, 0x4B},
                {"Pokemon Wanted", 0xA4, 0xA0},
                {"Wanted", 0xA6, 0xA2},
                {"Gender", 0xA8, 0xA4},
                {"Level", 0xAA, 0xA6},
                {"Options", 0xAE, 0xAA}
            };
        }

        namespace French {
            static const Deposit deposit[7] = {
                {"Retour", 0x45, 0x40},
                {"Quitter le GTS", 0x4F, 0x4B},
                {"Pokémon Recherché", 0xA4, 0xA0},
                {"Recherché", 0xA6, 0xA2},
                {"Genre", 0xA8, 0xA4},
                {"Niveau", 0xAA, 0xA6},
                {"Options", 0xAE, 0xAA}
            };
        }

        namespace Italian {
            static const Deposit deposit[7] = {
                {"Indietro", 0x45, 0x40},
                {"Esci dalla GTS", 0x4F, 0x4B},
                {"Cerca un Pokémon", 0xA4, 0xA0},
                {"Pokémon Richiesto", 0xA6, 0xA2},
                {"Sesso", 0xA8, 0xA4},
                {"Livello", 0xAA, 0xA6},
                {"Opzioni", 0xAE, 0xAA}
            };
        }

        static int depositConfig, getSettings[2], settings[3];
        static int optionsType;

        void ConfigurationKB(MenuEntry *entry) {
            static const vector<string> options = {"Pokemon", language("Gender", "Sexe", "Sesso"), language("Level", "Niveau", "Livello")};
            KeyboardPlus keyboard;

            start:
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, depositConfig) != -1) {
                if (depositConfig == 0) {
                    FindPkmnKB(entry);

                    if (Controller::IsKeyPressed(Key::B))
                        goto start;

                    settings[0] = pkmnID;

                    if (settings[0] != 0)
                        Message::Completed();

                    else goto start;
                }

                else {
                    choose:
                    if (keyboard.SetKeyboard(entry->Name() + ":", true, {language("Hacked", "Hacké", "Hackerato"), language("Normal", "Normal", "Legit")}, optionsType) != -1) {
                        if (optionsType == 0) {
                            vector<string> selection;

                            for (const Deposit &nickname : (currLang == Lang::ENG ? English::deposit : French::deposit))
                                selection.push_back(nickname.name);

                            if (keyboard.SetKeyboard(options[depositConfig] + ":", true, selection, getSettings[depositConfig - 1]) != -1) {
                                settings[depositConfig] = (depositConfig < 2) ? (currLang == Lang::ENG ? English::deposit[getSettings[depositConfig - 1]].val1 : French::deposit[getSettings[depositConfig - 1]].val1) : (currLang == Lang::ENG ? English::deposit[getSettings[depositConfig -1]].val2 : French::deposit[getSettings[depositConfig -1]].val2);
                                Message::Completed();
                                return;
                            }

                            else goto choose;
                        }

                        else {
                            vector<vector<string>> selection = {{language("Any", "Tout", "Qualsiasi"), language("Male", "Mâle", "Maschio"), language("Female", "Femelle", "Femmina")}, {language("Any", "Tout", "Qualsiasi"), "1 ~ 10", "11 ~ 20", "21 ~ 30", "31 ~ 40", "41 ~ 50", "51 ~ 60", "61 ~ 70", "71 ~ 80", "81 ~ 90", language("91 or higher", "91 ou plus", "91 o superiore")}};

                            if (keyboard.SetKeyboard(options[depositConfig] + ":", true, (depositConfig == 1 ? selection[0] : selection[1]), getSettings[depositConfig - 1]) != -1) {
                                settings[depositConfig] = getSettings[depositConfig - 1];
                                Message::Completed();
                                return;
                            }

                            else goto choose;
                        }
                    }

                    else goto start;
                }
            }
        }

        void Configuration(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x8C61E54, 0x8C61E56, 0x8C61E57},
                    {0x8C69470, 0x8C69472, 0x8C69473}
            )};

            for (int i = 0; i < 3; i ++) {
                if (settings[i] > 0)
                    (i == 0) ? Process::Write16(address[0], settings[0]) : Process::Write8(address[i], settings[i]);
            }
        }

        // Ty H4x0rSpooky for the cheat
        void BypassLimit(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x4375AC, 0x4642F4);
            static vector<u32> original(2);
            static bool saved = false;

            if (!ProcessPlus::Write32(address, {0xE3A00000, 0xEA000000}, original, entry, saved))
                return;
        }
    }

    namespace Profile {
        static const u32 offset = 0x8C646A4;

        struct Sprites {
            int id;
            const char *name;
        };

        namespace English {
            static const Sprites hackedIcons[3] = {
                {17, "Invisible"},
                {128, "Pokémon Center"},
                {129, "Gift"}
            };

            static const Sprites regularIcons[71] = {
                {0, "Serena"},
                {1, "Calem"},
                {2, "Sycamore"},
                {3, "Diantha"},
                {4, "Wikstrom"},
                {5, "Malva"},
                {6, "Drasna"},
                {7, "Siebold"},
                {8, "Viola"},
                {9, "Grant"},
                {10, "Korrina"},
                {11, "Ramos"},
                {12, "Clemont"},
                {13, "Valerie"},
                {14, "Olympia"},
                {15, "Wulfric"},
                {16, "Youngster"},
                {18, "Lass"},
                {19, "Lady"},
                {20, "Schoolgirl"},
                {21, "Battle Girl"},
                {22, "Schoolboy"},
                {23, "Rich Boy"},
                {24, "Female Ace Trainer"},
                {26, "Female Ranger"},
                {27, "Male Ace Trainer"},
                {28, "Male Ranger"},
                {29, "Madame"},
                {30, "Monsieur"},
                {31, "Black Belt"},
                {32, "Male Punk"},
                {33, "Fairy Tale Girl"},
                {34, "Shauna"},
                {35, "Tierno"},
                {36, "Trevor"},
                {37, "Brendan"},
                {38, "May"},
                {40, "Hiker"},
                {41, "Aroma Lady"},
                {42, "Male Schoolkid"},
                {43, "Female Schoolkid"},
                {44, "Black Belt"},
                {45, "Battle Girl"},
                {46, "Pokemaniac"},
                {47, "Fairy Tale Girl"},
                {48, "Victor Winstrate"},
                {49, "Victoria Winstrate"},
                {50, "Male Ranger"},
                {51, "Female Ranger"},
                {52, "Male Swimmer"},
                {53, "Hex Maniac"},
                {54, "Male Ace Trainer"},
                {55, "Female Ace Trainer"},
                {56, "Street Thug"},
                {57, "Delinquent"},
                {58, "Male Expert"},
                {59, "Female Expert"},
                {60, "Lady"},
                {61, "Rich Boy"},
                {62, "Ninja Boy"},
                {63, "Beauty"},
                {64, "Guitarist"},
                {65, "Lass"},
                {66, "Male Breeder"},
                {67, "Female Breeder"},
                {68, "Camper"},
                {69, "Picnicker"},
                {70, "Wally"},
                {71, "Steven"},
                {72, "Maxie"},
                {73, "Archie"}
            };
        }

        namespace French {
            static const Sprites regularIcons[71] = {
                {0, "Serena"},
                {1, "Calem"},
                {2, "Sycamore"},
                {3, "Diantha"},
                {4, "Wikstrom"},
                {5, "Malva"},
                {6, "Drasna"},
                {7, "Siebold"},
                {8, "Viola"},
                {9, "Grant"},
                {10, "Korrina"},
                {11, "Ramos"},
                {12, "Clemont"},
                {13, "Valerie"},
                {14, "Olympia"},
                {15, "Wulfric"},
                {16, "Jeune Dresseur"},
                {18, "Dresseuse"},
                {19, "Dame"},
                {20, "Écolière"},
                {21, "Fille de combat"},
                {22, "Écolier"},
                {23, "Jeune riche"},
                {24, "Dresseuse As"},
                {26, "Ranger Femme"},
                {27, "Dresseur As"},
                {28, "Ranger Homme"},
                {29, "Madame"},
                {30, "Monsieur"},
                {31, "Ceinture Noire"},
                {32, "Punk Homme"},
                {33, "Fille des contes"},
                {34, "Shauna"},
                {35, "Tierno"},
                {36, "Trevor"},
                {37, "Brendan"},
                {38, "May"},
                {40, "Randonneur"},
                {41, "Demoiselle Parfumée"},
                {42, "Écolier Homme"},
                {43, "Écolière Femme"},
                {44, "Ceinture Noire"},
                {45, "Fille de combat"},
                {46, "Pokémaniac"},
                {47, "Fille des contes"},
                {48, "Victor Winstrate"},
                {49, "Victoria Winstrate"},
                {50, "Ranger Homme"},
                {51, "Ranger Femme"},
                {52, "Nageur Homme"},
                {53, "Folle aux hexagones"},
                {54, "Dresseur As"},
                {55, "Dresseuse As"},
                {56, "Voyou de rue"},
                {57, "Délinquante"},
                {58, "Expert Homme"},
                {59, "Expert Femme"},
                {60, "Dame"},
                {61, "Jeune riche"},
                {62, "Garçon Ninja"},
                {63, "Belle"},
                {64, "Guitariste"},
                {65, "Dresseuse"},
                {66, "Éleveur Homme"},
                {67, "Éleveuse Femme"},
                {68, "Campeur"},
                {69, "Pique-niqueuse"},
                {70, "Wally"},
                {71, "Steven"},
                {72, "Maxie"},
                {73, "Archie"}
            };

            static const Sprites hackedIcons[3] = {
                {17, "Invisible"},
                {128, "Centre Pokémon"},
                {129, "Cadeau"}
            };
        }

        namespace Italian {
            static const Sprites hackedIcons[3] = {
                {17, "Invisibile"},
                {128, "Centro Pokémon"},
                {129, "Regalo"}
            };

            static const Sprites regularIcons[71] = {
                {0, "Serena"},
                {1, "Calem"},
                {2, "Platan"},
                {3, "Diantha"},
                {4, "Timeus"},
                {5, "Malva"},
                {6, "Lilia"},
                {7, "Narciso"},
                {8, "Violetta"},
                {9, "Lino"},
                {10, "Ornella"},
                {11, "Amur"},
                {12, "Lem"},
                {13, "Valérie"},
                {14, "Astra"},
                {15, "Edel"},
                {16, "Marmocchio"},
                {18, "Teenager"},
                {19, "Lady"},
                {20, "Studentessa"},
                {21, "Combat Girl"},
                {22, "Studente"},
                {23, "Elegantone"},
                {24, "Fantallenatrice"},
                {26, "Pokémon Ranger (F)"},
                {27, "Fantallenatore"},
                {28, "Pokémon Ranger (M)"},
                {29, "Madame"},
                {30, "Gentiluomo"},
                {31, "Cinturanera"},
                {32, "Ribelle"},
                {33, "Ragazza delle fiabe"},
                {34, "Shauna"},
                {35, "Tierno"},
                {36, "Trovato"},
                {37, "Brendon"},
                {38, "Vera"},
                {40, "Montanaro"},
                {41, "Profumina"},
                {42, "Scolaro"},
                {43, "Scolara"},
                {44, "Cinturanera"},
                {45, "Combat Girl"},
                {46, "Pokéfanatico"},
                {47, "Ragazza delle fiabe"},
                {48, "Vincenzo Vinci"},
                {49, "Vittoria Vinci"},
                {50, "Pokémon Ranger (M)"},
                {51, "Pokémon Ranger (F)"},
                {52, "Nuotatore"},
                {53, "Streghetta"},
                {54, "Fantallenatore"},
                {55, "Fantallenatrice"},
                {56, "Tipaccio"},
                {57, "Tipaccia"},
                {58, "Specialista (M)"},
                {59, "Specialista (F)"},
                {60, "Lady"},
                {61, "Elegantone"},
                {62, "Ninja Boy"},
                {63, "Bellezza"},
                {64, "Chitarrista"},
                {65, "Teenager"},
                {66, "Allevapokémon (M)"},
                {67, "Allevapokémon (F)"},
                {68, "Campeggiatore"},
                {69, "Picnic Girl"},
                {70, "Lino"},
                {71, "Rocco Petri"},
                {72, "Max"},
                {73, "Ivan"}
            };
        }

        int iconsAvailable = 0;
        static int iconCategory, getIcon;

        void Icons(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x8C79C43, 0x8C81347);

            int counter = 0;
            vector<string> hackedOptions;
            static vector<string> regularOptions;
            KeyboardPlus keyboard;

            for (const Sprites &nickname : (currLang == Lang::ENG ? English::regularIcons : French::regularIcons)) {
                if (iconsAvailable < ((group == Group::XY) ? 35 : 71)) {
                    regularOptions.push_back(nickname.name);
                    iconsAvailable++;
                }

                else break;
            }

            start:
            if (keyboard.SetKeyboard(entry->Name() + ":", true, {language("Hacked", "Hacké", "Hackerate"), language("Normal", "Normal", "Normali")}, iconCategory) != -1) {
                if (iconCategory != 0) {
                    if (keyboard.SetKeyboard(entry->Name() + ":", true, regularOptions, getIcon) != -1) {
                        Process::Write8(address, (currLang == Lang::ENG ? English::regularIcons[getIcon].id : French::regularIcons[getIcon].id));
                        goto end;
                    }

                    else goto start;
                }

                else {
                    for (const Sprites &nickname : (currLang == Lang::ENG ? English::hackedIcons : French::hackedIcons)) {
                        if (counter < 3) {
                            hackedOptions.push_back(nickname.name);
                            counter++;
                        }

                        else break;
                    }

                    if (keyboard.SetKeyboard(entry->Name() + ":", true, hackedOptions, getIcon) != -1) {
                        Process::Write8(address, (currLang == Lang::ENG ? English::hackedIcons[getIcon].id : French::hackedIcons[getIcon].id));
                        goto end;
                    }

                    else goto start;
                }

                return;
                end:
                Message::Completed();
            }
        }

        static u32 nicesReceived;

        void Nices(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x8C82B90, 0x8C8B35C);

            if (KB<u32>(entry->Name() + ":", true, false, 5, nicesReceived, 0, 0, 99999, Callback32)) {
                if (Process::Write32(address, nicesReceived))
                    Message::Completed();
            }
        }

        static u32 wishesReceived;

        void Wishes(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x8C82B94, 0x8C8B360);

            if (KB<u32>(entry->Name() + ":", true, false, 5, wishesReceived, 0, 0, 99999, Callback32)) {
                if (Process::Write32(address, wishesReceived))
                    Message::Completed();
            }
        }

        static string messageVal;

        void Message(MenuEntry *entry) {
            static u32 address = Helpers::GetVersion(0x8C79CB8, 0x8C813BC);
            static int length;

            if (Helpers::TextColorizer(Helpers::GetVersion(0x8C79CB8, 0x8C813BC))) {
                length = 12;
                address = Helpers::GetVersion(0x8C79CB8, 0x8C813BC) + 0x8;
            }

            else {
                length = 16;
                address = Helpers::GetVersion(0x8C79CB8, 0x8C813BC);
            }

            if (KB<string>(entry->Name() + ":", true, false, length, messageVal, "")) {
                if (Process::WriteString(address, messageVal, StringFormat::Utf16))
                    Message::Completed();
            }
        }

        static u8 historyIndex;
        static int getAction;

        void History(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x8C84C7C, 0x8C8D448);
            static const vector<string> options = {language("Battle", "Combat", "Battaglia"), language("Trade", "Echange", "Scambio"), language("O-Power", "O-Aura", "Poteri O"), "Global Trade Station", language("Battle Spot", "Coin combats", "Punto Lotta"), language("Wonder Trade", "Echange miracle", "Scambio prodigioso")};
            KeyboardPlus keyboard;

            if (KB<u8>(language("Index:", "Indexe:", "Indice"), true, false, 1, historyIndex, 0, 1, 6, Callback8)) {
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, getAction) != -1) {
                    if (Process::Read8(address, data8) && data8 != 6)
                        Process::Write8(address, 6);

                    if (Process::Write8(address + historyIndex, getAction + 1))
                        Message::Completed();
                }
            }
        }

        static int countryID, getCountry, regionID, getRegion;

        // Ty H4x0rSpooky for the cheat
        void Location(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x8C79C62, 0x41B088, 0x53ED50},
                    {0x8C81366, Helpers::PickGame<u32>(0x43DA28, 0x43DA20), Helpers::PickGame<u32>(0x579820, 0x579818)}
            )};

            vector<string> options;
            KeyboardPlus keyboard;

            for (const Geograph &nickname : (currLang == Lang::ENG ? CTRPluginFramework::English::allCountries : (currLang == Lang::FRE ? CTRPluginFramework::French::allCountries : CTRPluginFramework::Italian::allCountries))){
                options.push_back(nickname.name);
            }

            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, getCountry) != -1) {
                int countryID;

                if (currLang == Lang::ITA) {
                    countryID = CTRPluginFramework::Italian::allCountries[getCountry].id;
                }
                else if (currLang == Lang::ENG) {
                    countryID = CTRPluginFramework::English::allCountries[getCountry].id;
                }
                else if (currLang == Lang::FRE) {
                    countryID = CTRPluginFramework::French::allCountries[getCountry].id;
                }

                if (Process::Write16(address[0], (countryID << 8 | regionID))) {
                    if (Process::Write32(address[1], Helpers::GetVersion(0xEB048F30, 0xEB04EF7C))) {
                        ProcessPlus::Write32(address[2], { 0xE59F0004, 0xE5900000, 0xE12FFF1E, Helpers::GetVersion<u32>(0x8C79C60, 0x8C81364) });
                    }
                }

                Message::Completed();
            }
        }

        static int chooseActivity, acvitityType;
        static u32 activityVal[2], existingVals[3];

        void Links(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x8C82ADC, 0x8C82AD4},
                    {0x8C8B2A8, 0x8C8B2A0}
            )};

            static const vector<string> options = {language("Battles", "Combats", "Battaglie"), language("Trades", "Echanges", "Scambi")};
            KeyboardPlus keyboard;

            start:
            if (keyboard.SetKeyboard(language("Which one?", "Lequel?", "Quale?"), true, options, chooseActivity) != -1) {
                pick:
                for (int i = 0; i < sizeof(existingVals) / sizeof(existingVals[0]); i++)
                    Process::Read32(address[chooseActivity] + (i * 0x10), existingVals[i]);

                if (keyboard.SetKeyboard(language("Where would you like to write the value to?\n\nKeep in mind that these values do accumulate with each other.", "Où aimeriez-vous écrire la valeur?\n\nGardez à l'esprit que ces valeurs s'accumulent les unes avec les autres.", "Dove desideri scrivere il valore?\n\nTieni presente che questi valori si accumulano\ntra di loro.") << "\n\nLink: " << Color::Gray << to_string(existingVals[0]) << Color::White << "\nWiFi: " << Color::Gray << to_string(existingVals[1]) << Color::White << "\nIR: " << Color::Gray << to_string(existingVals[2]) << Color::White << "\n\n" + language("Total: ", "Total: ", "Totale:") << Color::Gray << to_string(existingVals[0] + existingVals[1] + existingVals[2]), true, {"Link", "WiFi", "IR"}, acvitityType) != -1) {
                    if (KB<u32>(language("Amount:", "Montant:", "Quantità:"), true, false, 6, activityVal[chooseActivity], 0, 0, 999999, Callback32)) {
                        if (Process::Write32(address[chooseActivity] + (acvitityType * 0x10), activityVal[chooseActivity]))
                            Message::Completed();
                    }

                    else goto pick;
                }

                else goto start;
            }
        }

        static u8 survey, surveyDest;

        void MiniSurvey(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x8C7D228, 0x8C7D22E},
                    {0x8C8545C, 0x8C85462}
            )};

            if (KB<u8>(language("Survey (copy from):", "Enquête (copier depuis):", "Sondaggio (copia da):"), true, false, 1, survey, 0, 1, 6, Callback8)) {
                if (KB<u8>(language("Survey (copy to):", "Enquête (copie vers):", "Sondaggio (copia verso):"), true, false, 1, surveyDest, 0, 1, 6, Callback8)) {
                    for (int i = 0; i < address.size(); i++) {
                        if (surveyDest != survey)
                            Process::Write8(address[i] + (surveyDest - 1), ProcessPlus::Read8(address[i] + (survey - 1)));

                        else return;
                    }

                    Message::Completed();
                }
            }
        }

        static int greetStat;
        static u32 greetAmount[2];

        void Greets(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x8C82CA0, 0x8C82B98},
                    {0x8C8B46C, 0x8C8B364}
            )};

            static const vector<string> options = {language("Today", "Aujourd'hui", "Oggi"), language("Total", "Total", "Totale")};
            KeyboardPlus keyboard;

            start:
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, greetStat) != -1) {
                if (KB<u32>(options[greetStat] + ":", true, false, (greetStat == 0 ? 4 : 9), greetAmount[greetStat], 0, 0, (greetStat == 0 ? 9999 : 999999999), (greetStat == 0 ? Callback16 : Callback32))) {
                    if (greetStat == 0 ? Process::Write16(address[greetStat], greetAmount[greetStat]) : Process::Write32(address[greetStat], greetAmount[greetStat]))
                        Message::Completed();
                }

                else goto start;
            }
        }
    }

    static u8 guageFilled;

    void GuageKB(MenuEntry *entry) {
        if (KB<u8>(entry->Name() + ":", true, false, 2, guageFilled, 0, 0, 10, Callback8))
            Message::Completed();
    }

    void Guage(MenuEntry *entry) {
        static const u32 address = Helpers::GetVersion(0x8C7BB64, 0x8C83D94);

        if (Process::Read8(address, data8) && data8 != guageFilled)
            Process::Write8(address, guageFilled);
    }

    bool AllOPowers(void) {
        static const u32 address = Helpers::GetVersion(0x8C7BB01, 0x8C83D31);

        for (int i = 0; i < 63; i++) {
            if (Bit::Read8(address + i, data8, true) && data8 != 1)
                return false;
        }

        return true;
    }

    void UnlockEveryPower(MenuEntry *entry) {
        static const u32 address = Helpers::GetVersion(0x8C7BB01, 0x8C83D31);

        if (!AllOPowers()) {
            for (int i = 0; i < 63; i++) {
                if (Bit::Read8(address + i, data8, true) && data8 != 1)
                    Bit::Write8(address + i, 1, true);
            }

             Message::Completed();
             return;
        }

        else Message::Warning();
    }

    static string shoutOutVal;

    void ShoutOut(MenuEntry *entry) {
        static u32 address = Helpers::GetVersion(0x8C79D62, 0x8C81466);
        static int length;

        if (Helpers::TextColorizer(Helpers::GetVersion(0x8C79D62, 0x8C81466))) {
            length = 12;
            address = Helpers::GetVersion(0x8C79D62, 0x8C81466) + 0x8;
        }

        else {
            length = 16;
            address = Helpers::GetVersion(0x8C79D62, 0x8C81466);
        }

        if (KB<string>(entry->Name() + ":", true, false, length, shoutOutVal, "")) {
            if (Process::WriteString(address, shoutOutVal, StringFormat::Utf16))
                Message::Completed();
        }
    }

    static int section, canClear[2];

    void ClearUsersKB(MenuEntry *entry) {
        static const vector<string> options = {language("Friends", "Amis", "Amici"), language("Acquaintances", "Connaissances", "Persone incontrate")};
        KeyboardPlus keyboard;

        if (keyboard.SetKeyboard(entry->Name() + ":", true, options, section) != -1) {
            canClear[section] = 1;
            Message::Completed();
        }
    }

    void ClearUsers(MenuEntry *entry) {
        static const vector<u32> address = {
            Helpers::GetVersion<u32>(
                {0x8C74DFC, 0x8D989E8, 0x8C79C2C, 0x8D989F4},
                {0x8C7C500, 0x8DC21C0, 0x8C81330, 0x8DC21CC}
        )};

        for (int i = 0; i < address.size(); i++) {
            if (canClear[(int)(i / 2)])
                Process::Write32(address[i], 0);
        }
    }

    void BypassHackedIcons(MenuEntry *entry) {
        static const u32 address = Helpers::GetVersion(0x4AF688, 0x4E7194);
        static u32 original;
        static bool saved = false;

        if (!ProcessPlus::Write32(address, 0xE3A00000, original, entry, saved))
            return;
    }
}