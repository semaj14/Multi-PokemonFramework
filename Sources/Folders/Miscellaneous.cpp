#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

namespace Misc {
    static int weatherLocation, weatherToggle;

    void WeatherKB(MenuEntry *entry) {
        static const vector<string> options = {language("Route 113", "Route 113", "Percorso 113"), language("Route 119", "Route 119", "Percorso 119"), language("Route 120", "Route 120", "Percorso 120"), language("Jagged Pass", "Le Sentier Étroit", "Passo Selvaggio"), language("East Hoenn", "l'Est d'Hoenn", "Hoenn Est")};
        static const vector<string> conditions = {language("Snow", "Neige", "Neve"), language("Rain", "Pluie", "Pioggia"), language("Rain", "Pluie", "Pioggia"), language("Snow", "Neige", "Neve"), Helpers::PickGame(language("Extremely Harsh Sunlight", "Soleil ardent", "Luce solare estremamente intensa"), language("Heavy Rain", "Pluie diluvienne", "Pioggia battente"))};
        KeyboardPlus keyboard;

        if (keyboard.SetKeyboard(entry->Name() + ":", true, options, weatherLocation) != -1) {
            if (keyboard.SetKeyboard(conditions[weatherLocation] + ":", true, {language("On", "Allumé", "On"), language("Off", "Eteint", "Off")}, weatherToggle) != -1)
                Message::Completed();
        }
    }

    static const vector<int> weatherFlags = {1, 4, 1, 1, Helpers::PickGame(2, 4)};

    void Weather(MenuEntry *entry) {
        static const vector<vector<u32>> address = {{Helpers::PickGame<u32>(0x3FE54C, 0x3FE544)}, {0x8C81B56, 0x8C81B5E, 0x8C81B58, 0x8C81B5A, 0x8C81F37}};
        static u32 original;
        static bool saved = false;

        if (ProcessPlus::Write32(address[0][0], 0xE320F000, original, entry, saved)) {
            if (Bit::Read8(address[1][weatherLocation], data8, true) && data8 != (weatherToggle == 0 ? weatherFlags[weatherLocation] : 0))
                if (!Bit::Write8(address[1][weatherLocation], (weatherToggle == 0 ? weatherFlags[weatherLocation] : 0), true))
                    return;
        }
    }

    void IsRenamable(MenuEntry *entry) {
        static const u32 address = Helpers::AutoRegion(Helpers::GetVersion(0x4B1680, Helpers::PickGame(0x4EA990, 0x4EA998)), Helpers::GetVersion(0x4AA2C0, 0x4C6F64));
        static u32 original;
        static bool saved = false;

        if (!ProcessPlus::Write32(address, 0xE3A00001, original, entry, saved))
            return;
    }

    void LearnAnyTeachables(MenuEntry *entry) {
        static const u32 address = Helpers::AutoRegion(Helpers::GetVersion(0x4A0540, Helpers::PickGame(0x4D051C, 0x4D0514)), Helpers::GetVersion(0x490D34, 0x4ACBEC));
        static u32 original;
        static bool saved = false;

        if (!ProcessPlus::Write32(address, 0xE3A00001, original, entry, saved))
            return;
    }

    void GetDayCareEgg(MenuEntry *entry) {
        static const u32 address = Helpers::AutoRegion(Helpers::GetVersion(0x438C50, Helpers::PickGame(0x4658A4, 0x46589C)), Helpers::GetVersion(0x4466A8, Helpers::PickGame(0x45C628, 0x45C62C)));
        static vector<u32> original(3);
        static bool saved = false;

        if (!ProcessPlus::Write32(address, {0xE3A01001, Helpers::AutoRegion(0xE5C011E8, 0xE5C011E0), Helpers::AutoRegion(0xEA00209B, 0xEA00684B)}, original, entry, saved))
            return;
    }

    void FastDialogs(MenuEntry *entry) {
        static const vector<u32> address = {
            Helpers::AutoRegion(
                Helpers::GetVersion<u32>(
                    {0x3F6FB4, 0x3F7818},
                    {0x419A34, 0x41A2A4}),

                Helpers::GetVersion<u32>(
                    {0x3BFBF4, 0x3C0498},
                    {Helpers::PickGame<u32>(0x3D12B4, 0x3D12B8), Helpers::PickGame<u32>(0x3D1B58, 0x3D1B5C)}
        ))};

        static vector<u32> original(2);
        static bool saved = false;

        if (!ProcessPlus::Write32(address, {0xE3A04003, 0xE3A05003}, original, entry, saved))
            return;
    }

    namespace Gen6 {
        void InstantEggHatch(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x4A22F4, 0x4D2278);
            static u32 original;
            static bool saved = false;

            if (!ProcessPlus::Write32(address, 0xE3A00000, original, entry, saved))
                return;
        }

        void ViewValuesInSummary(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x153184, 0x153230, 0x4A23E4, 0x4A2430, 0x4A25E4, 0x4A2630, 0x4A2398},
                    {0x1531AC, 0x15328C, Helpers::PickGame<u32>(0x4D2370, 0x4D2368), Helpers::PickGame<u32>(0x4D23BC, 0x4D23B4), Helpers::PickGame<u32>(0x4D2534, 0x4D252C), Helpers::PickGame<u32>(0x4D2580, 0x4D2578), Helpers::PickGame<u32>(0x4D2324, 0x4D231C)}
            )};

            static const vector<vector<u32>> instruction = {
                {{Helpers::GetVersion(0xEA0060EC, 0xEA006283)}, {Helpers::GetVersion(0xEA0060C1, 0xEA00624B)}, {Helpers::GetVersion(0xEAF2C304, Helpers::PickGame(0xEAF2032B, 0xEAF2032D))}, {Helpers::GetVersion(0xEAF2C2FE, Helpers::PickGame(0xEAF20325, 0xEAF20327))}, {Helpers::GetVersion(0xEAF2C2B4, Helpers::PickGame(0xEAF202EA, 0xEAF202EC))}, {Helpers::GetVersion(0xEAF2C2AE, Helpers::PickGame(0xEAF202E4, 0xEAF202E6))}, {Helpers::GetVersion(0xEAF2C30A, Helpers::PickGame(0xEAF20331, 0xEAF20333))}},
                {{Helpers::GetVersion(0xEA0060E1, 0xEA006278)}, {Helpers::GetVersion(0xEA0060B6, 0xEA006240)}, {Helpers::GetVersion(0xEAF2C2E1, Helpers::PickGame(0xEAF20308, 0xEAF2030A))}, {Helpers::GetVersion(0xEAF2C2D9, Helpers::PickGame(0xEAF20300, 0xEAF20302))}, {Helpers::GetVersion(0xEAF2C29E, Helpers::PickGame(0xEAF202D4, 0xEAF202D6))}, {Helpers::GetVersion(0xEAF2C296, Helpers::PickGame(0xEAF202CC, 0xEAF202CE))}, {Helpers::GetVersion(0xEAF2C2E9, Helpers::PickGame(0xEAF20310, 0xEAF20312))}}
            };

            static const vector<u32> original(7, 0xE92D4070);

            if (entry->Hotkeys[0].IsDown())
                ProcessPlus::Write32(address, instruction[0]);

            else if (entry->Hotkeys[1].IsDown())
                ProcessPlus::Write32(address, instruction[1]);

            else ProcessPlus::Write32(address, original);
        }

        // Ty H4x0rSpooky for the cheat
        void NoOutlines(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x362ED8, 0x37A140);
            static vector<u32> original(2);
            static bool saved = false;

            if (!ProcessPlus::Write32(address, {0, 0}, original, entry, saved))
                return;
        }
    }

    namespace Gen7 {
        void InstantEggHatch(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x5977C0, 0x493668},
                    {0x5BBE40, 0x4AF604}
            )};

            static vector<u32> original(7);
            static u32 revert;
            static bool saved[2] = {false, false};

            if (ProcessPlus::Write32(address[0], {0xE59D000C, 0xE59F500C, 0xE1500005, 0x03A00000, 0x11A00004, 0xE12FFF1E, 0x006D08C0}, original, entry, saved[0])) {
                if (!ProcessPlus::Write32(address[1], Helpers::GetVersion(0xEB041054, 0xEB04320D), revert, entry, saved[1]))
                    return;
            }
        }

        void ViewValuesInSummary(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x49369C, 0x493A08, 0x4937CC, 0x493818, 0x493A54, 0x493AA0, 0x493780},
                    {0x4AF638, 0x4AF9A4, 0x4AF768, 0x4AF7B4, 0x4AF9F0, 0x4AFA3C, 0x4AF71C}
            )};

            static const vector<vector<u32>> instruction = {
                Helpers::GetVersion<u32>({0xEAFFFCFD, 0xEAFFFC22, 0xEAFFFD15, 0xEAFFFD0F, 0xEAFFFD14, 0xEAFFFD0E, 0xEAFFFD1B}, {0xEAFFFCE1, 0xEAFFFC06, 0xEAFFFCF9, 0xEAFFFCF3, 0xEAFFFCF8, 0xEAFFFCF2, 0xEAFFFCFF}),
                Helpers::GetVersion<u32>({0xEAFFFCE1, 0xEAFFFC06, 0xEAFFFCF9, 0xEAFFFCF3, 0xEAFFFCF8, 0xEAFFFCF2, 0xEAFFFCFF}, {0xEAFFFC82, 0xEAFFFBA7, 0xEAFFFCD6, 0xEAFFFCCE, 0xEAFFFCC6, 0xEAFFFCBE, 0xEAFFFCDE})
            };

            static const vector<u32> original(7, 0xE92D4070);

            if (entry->Hotkeys[0].IsDown())
                ProcessPlus::Write32(address, instruction[0]);

            else if (entry->Hotkeys[1].IsDown())
                ProcessPlus::Write32(address, instruction[1]);

            else ProcessPlus::Write32(address, original);
        }

        void NoOutlines(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x41CFCC, Helpers::PickGame(0x42FBA4, 0x42FBA8));
            static u32 original;
            static bool saved = false;

            if (!ProcessPlus::Write32(address, 0xE320F000, original, entry, saved))
                return;
        }
    }

    // Ty H4x0rSpooky for the cheat
    void BypassTextRestricts(MenuEntry *entry) {
        static const u32 address = Helpers::AutoRegion(Helpers::GetVersion(0x38DE64, 0x3A47D4), Helpers::GetVersion(0x353954, 0x35D0D8)); // Port to all games
        static u32 original;
        static bool saved = false;

        if (!ProcessPlus::Write32(address, 0xEA00003F, original, entry, saved))
            return;
    }

    // Custom Keyboard stuff. Big thanks to H4x0rSpooky for the help and the finding of a stable pointer.

    static u8 key;
    static u32 unicode;
    static u32 vals[0x81];

    void CustomKeyboard(MenuEntry *entry) {
        static u32 offset;
        static const u32 pointer = Helpers::GetVersion(0x8000460, 0x8000470);

        Process::Read32(pointer, offset);
        Process::Read32(offset + 0x5C, offset);
        offset += 0x27C;

        if (Process::Read16(offset + 0x84, data16) && data16 == 0x5544)
            Process::CopyMemory((u32*)offset, vals, 0x81);
    }

    void CustomKeyboardConfig(MenuEntry *entry) {
        static u32 offset;
        static const u32 pointer = Helpers::GetVersion(0x8000460, 0x8000470);

        vector<string> listOfFiles, listOfFileNames;
        string extension = ".bin";
        Directory directory("Keyboard");
        directory.ListFiles(listOfFiles, extension);
        listOfFileNames = listOfFiles;
        int index = listOfFileNames.size();

        if (index >= 20) {
            if (MessageBox(CenterAlign(language("Limit reached! Erase old backups?", "Limite atteinte! Supprimer les anciennes sauvegardes?", "Limite raggiunto! Cancellare i vecchi backup?")), DialogType::DialogYesNo, ClearScreen::Both)()) {
                for (int i = 0; i < index; i++)
                    File::Remove(language("Keyboard/", "Keyboard/", "Tastiera/") + listOfFileNames[i]);

                MessageBox(CenterAlign(language("All backups have been erased.", "Toutes les sauvegardes ont été effacées.", "Tutti i backup sono stati cancellati.")), DialogType::DialogOk, ClearScreen::Both)();
            }

            return;
        }

        int mode;
        string fileName;
        static const vector<string> options = {language("Export", "Exporter", "Esporta"), language("Import", "Importer", "Importa")};
        KeyboardPlus keyboard;

        Process::Read32(pointer, offset);
        Process::Read32(offset + 0x5C, offset);
        offset += 0x27C;

        if (Process::Read16(offset + 0x84, data16) && data16 == 0x5544) {
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, mode) != -1) {
                if (mode == 0) {
                    if (!Directory::IsExists(language("Keyboard", "Keyboard", "Tastiera")))
                        Directory::Create(language("Keyboard", "Keyboard", "Tastiera"));

                    if (index <= 20) {
                        if (KB<string>(language("Name:", "Nom:", "Nome:"), true, false, 16, fileName, "")) {
                            File dumpFile(language("Keyboard/", "Keyboard/", "Tastiera/") + fileName + extension, File::RWC);
                            dumpFile.Dump(offset, 0x81);
                            Message::Completed();
                            return;
                        }
                    }
                }

                if (mode == 1) {
                    if (index == 0) {
                        MessageBox(CenterAlign(language("You have 0 backup(s) to recover from!", "Vous n'avez aucune sauvegarde à récupérer!", "Hai 0 backup da cui ripristinare!")), DialogType::DialogOk, ClearScreen::Both)();
                        return;
                    }

                    if (index >= 1) {
                        keyboard.Populate(listOfFileNames);
                        int fileIndex = keyboard.Open();

                        if (fileIndex >= 0) {
                            File injectFile(language("Keyboard/", "Keyboard/", "Tastiera/") + listOfFileNames[fileIndex]);
                            injectFile.Read(vals, 0x81);
                            entry->SetGameFunc(CustomKeyboard);
                            Message::Completed();
                            return;
                        }
                    }
                }
            }
        }
    }

    void CustomKeys(MenuEntry *entry) {
        static u32 offset;
        static const u32 pointer = Helpers::GetVersion(0x8000460, 0x8000470);
        static const vector<u8> clear(0x81, 0);

        Process::Read32(pointer, offset);
        Process::Read32(offset + 0x5C, offset);
        offset += 0x27C;

        if (Process::Read16(offset + 0x84, data16) && data16 == 0x5544) {
            if (Controller::IsKeyPressed(Key::Y))
                Process::CopyMemory((u32*)offset, clear.data(), 0x81);

            if (entry->Hotkeys[0].IsPressed()) {
                Sleep(Seconds(.5));

                if (KB<u8>(language("Key:", "Touches:", "Chiave:"), true, false, 3, key, 0, 1, 65, Callback8)) {
                    Sleep(Seconds(.5));

                    if (KB<u32>("Unicode:", true, true, 4, unicode, 0, 0, 0xFFFF, Callback32))
                        Process::Write16(offset + (2 * (key - 1)), unicode);
                }
            }
        }
    }

    void PatchColorCrash(MenuEntry *entry) {
        static const string s(Helpers::GetVersion("8K2589", Helpers::PickGame("96FF7H", "96FF79")));
        static u32 original;
        static bool saved = false;

        ProcessPlus process;
        unsigned int x = stoul(process.Address(s, -5), nullptr, 16);

        if (!ProcessPlus::Write32(x + Helpers::GetVersion(0x2000, 0), 0xE3B01000, original, entry, saved))
            return;
    }
}