#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework {
    u16 spwnSpecies;
    u8 spawnLv;
    u8 spwnForm;
    int pkmnID = 0;

    int MatchPkmn(Pokemon &output, string &input) {
        int index = 0;
        output.name.clear();
        string lowerCase(input);

        for (char &character : lowerCase)
            character = tolower(character);

        // Parse our possibilities to find the matches
        for (const string &pkmn : (currLang == Lang::ENG ? English::allPkmn : French::allPkmn)) {
            string::iterator iterator = lowerCase.begin();
            string::const_iterator pokeIterator = pkmn.begin();

            // Parse every letter of input while it matches the Pokémon's name
            while (iterator != lowerCase.end() && pokeIterator != pkmn.end() && *iterator == tolower(*pokeIterator)) {
                ++iterator;
                ++pokeIterator;
            }

            if (index < Helpers::AutoRegion(721, Helpers::GetVersion(802, 807))) {
                if (iterator == lowerCase.end()) {
                    output.name.push_back(pkmn);
                    output.choiceNo.push_back(index);
                }
            }

            index++;
        }

        return (output.choiceNo.size());
    }

    void PkmnInputChange(Keyboard &keyboard, KeyboardEvent &event) {
        string &input = keyboard.GetInput();
        Pokemon matches;
        int count = MatchPkmn(matches, input), choice;

        // If the user removed a letter, clear the input and set an error
        if (event.type == KeyboardEvent::CharacterRemoved) {
            input = "";
            keyboard.SetError(language("Type a letter to search for a Pokémon.", "Tapez une lettre pour chercher un Pokémon.", "Digita una lettera per cercare un Pokémon."));
            return;
        }

         // Else if input's length is inferior than 3, ask for more letters
        else if (input.size() < 3) {
            keyboard.SetError(language("Not enough letters to do the search.","Pas assez de lettres pour effectuer la recherche.", "Non ci sono abbastanza lettere per effettuare la ricerca."));
            return;
        }

        // If we don't have any matches, tell the user
        if (!count) {
            keyboard.SetError(language("Nothing matches your input. Please try again.", "Rien ne correspond à votre saisie. Veuillez réessayer.", "Non c'è nulla che corrisponda al tuo input. Si prega di riprovare."));
            return;
        }

        // If we have only one matches, complete the input
        if (count == 1) {
            pkmnID = matches.choiceNo[0] + 1;
            OSD::Notify(Color::LimeGreen << language("Success", "Succès", "Successo") << Color::White << language("! Selected: ", "! Sélectionné: ", "! Selezionato: ") << matches.name[0]);
            keyboard.Close();
            return;
        }

        // If we have less than or equal to ten matches, populate a list keyboard
        if (count > 1 && count <= 10) {
            Keyboard kb(matches.name);
            kb.CanAbort(false);
            kb.DisplayTopScreen = false;
            choice = kb.Open();

            if (choice >= 0) {
                pkmnID = matches.choiceNo[choice] + 1;
                OSD::Notify(Color::LimeGreen << language("Success", "Succès", "Successo") << Color::White << language("! Selected: ", "! Sélectionné: ", "!Selezionato: ") << matches.name[choice]);
                keyboard.Close();
                return;
            }
        }

        // We have too much results, the user must keep typing letters
        keyboard.SetError(language("Too many results: ", "Trop de résultats: ", "Troppi risultati: ") + to_string(count) + language("\nType more letters to narrow down the results.", "\nEntrez plus de lettres pour affiner les résultats.", "\nDigita altre lettere per restringere i risultati."));
    }

    void FindPkmnKB(MenuEntry *entry) {
        string output;

        if (KB<string>("Pokémon:", true, 11, output, "", PkmnInputChange))
            return;
    }

    int abilityID;

    int MatchAbility(Ability &output, string &input) {
        int index = 0;
        output.name.clear();
        string lowerCase(input);

        for (char &character : lowerCase)
            character = tolower(character);

        // Parse our possibilities to find the matches
        for (const string &ability : (currLang == Lang::ENG ? English::allAbilities : French::allAbilities)) {
            string::iterator iterator = lowerCase.begin();
            string::const_iterator itemIterator = ability.begin();

            // Parse every letter of input while it matches the ability's name
            while (iterator != lowerCase.end() && itemIterator != ability.end() && *iterator == tolower(*itemIterator)) {
                ++iterator;
                ++itemIterator;
            }

            if (index < Helpers::AutoRegion(Helpers::GetVersion(188, 191), 233)) {
                if (iterator == lowerCase.end()) {
                    output.name.push_back(ability);
                    output.choiceNo.push_back(index);
                }
            }

            index++;
        }

        return (output.choiceNo.size());
    }

    void AbilityInputChange(Keyboard &keyboard, KeyboardEvent &event) {
        string &input = keyboard.GetInput();
        Ability matches;
        int count = MatchAbility(matches, input), choice;

        // If the user removed a letter, clear the input and set an error
        if (event.type == KeyboardEvent::CharacterRemoved) {
            input = "";
            keyboard.SetError(language("Type a letter to search for an ability.", "Tapez une lettre pour chercher une capacité.", "Digitare una lettera per cercare un'abilità."));
            return;
        }

         // Else if input's length is inferior than 3, ask for more letters
        else if (input.size() < 3) {
            keyboard.SetError(language("Not enough letters to do the search.","Pas assez de lettres pour effectuer la recherche.", "Non ci sono abbastanza lettere per effettuare la ricerca."));
            return;
        }

        // If we don't have any matches, tell the user
        if (!count) {
            keyboard.SetError(language("Nothing matches your input. Please try again.", "Rien ne correspond à votre saisie. Veuillez réessayer.", "Non c'è nulla che corrisponda al tuo input. Si prega di riprovare."));
            return;
        }

        // If we have only one matches, complete the input
        if (count == 1) {
            abilityID = matches.choiceNo[0] + 1;
            input = matches.name[0];
            return;
        }

        // If we have less than or equal to ten matches, populate a list keyboard
        if (count <= 10) {
            Keyboard kb(matches.name);
            kb.CanAbort(false);
            kb.DisplayTopScreen = false;
            choice = kb.Open();

            if (choice >= 0) {
                abilityID = matches.choiceNo[choice] + 1;
                input = matches.name[choice];
                return;
            }
        }

        // We have too much results, the user must keep typing letters
        keyboard.SetError(language("Too many results: ", "Trop de résultats: ", "Troppi risultati: ") + to_string(count) + language("\nType more letters to narrow down the results.", "\nEntrez plus de lettres pour affiner les résultats.", "Digita più lettere per restringere i risultati."));
    }

    void FindAbilityKB(MenuEntry *entry) {
        string output;

        if (KB<string>(language("Ability:", "Capacité:", "Abilità:"), true, 16, output, "", AbilityInputChange))
            return;

        abilityID = 0;
    }

    int heldItemID;

    int MatchHeldItem(HeldItem &output, string &input) {
        static const vector<int> ignored = {112, 113, 114, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 425, 426, 621, 806, 807, 808, 809, 810, 811, 812, 813, 814, 815, 816, 817, 818, 819, 820, 821, 822, 823, 824, 825, 826, 827, 828, 829, 830, 831, 832, 833, 834, 836, 837, 838, 839, 847, 858, 860, 861, 862, 863, 864, 865, 866, 867, 868, 869, 870, 871, 872, 873, 874, 875, 876, 877, 884, 885, 886, 887, 888, 889, 890, 891, 892, 893, 894, 895, 896, 897, 898, 899, 900, 901, 902, 926, 927, 928, 929, 930, 931};        int index = 0;
        output.name.clear();
        string lowerCase(input);

        for (char &character : lowerCase)
            character = tolower(character);

        // Parse our possibilities to find the matches
        for (const string &item : (currLang == Lang::ENG ? English::allItems : French::allItems)) {
            string::iterator iterator = lowerCase.begin();
            string::const_iterator itemIterator = item.begin();

            // Parse every letter of input while it matches the held item's name
            while (iterator != lowerCase.end() && itemIterator != item.end() && *iterator == tolower(*itemIterator)) {
                ++iterator;
                ++itemIterator;
            }

            if (index < Helpers::AutoRegion(Helpers::GetVersion(717, 775), Helpers::GetVersion(920, 959))) {
                if (*find(ignored.begin(), ignored.end(), index) != index) {
                    if (iterator == lowerCase.end()) {
                        output.name.push_back(item);
                        output.choiceNo.push_back(index);
                    }
                }
            }

            index++;
        }

        return (output.choiceNo.size());
    }

    void ItemInputChange(Keyboard &keyboard, KeyboardEvent &event) {
        string &input = keyboard.GetInput();
        HeldItem matches;
        int count = MatchHeldItem(matches, input), choice;

        // If the user removed a letter, clear the input and set an error
        if (event.type == KeyboardEvent::CharacterRemoved) {
            input = "";
            keyboard.SetError(language("Type a letter to search for an item.", "Tapez une lettre pour chercher un objet.", "Digitare una lettera per cercare un elemento."));
            return;
        }

         // Else if input's length is inferior than 3, ask for more letters
        else if (input.size() < 3) {
            keyboard.SetError(language("Not enough letters to do the search.","Pas assez de lettres pour effectuer la recherche.", "Non ci sono abbastanza lettere per effettuare la ricerca."));
            return;
        }

        // If we don't have any matches, tell the user
        if (!count) {
            keyboard.SetError(language("Nothing matches your input. Please try again.", "Rien ne correspond à votre saisie. Veuillez réessayer.", "Non c'è nulla che corrisponda al tuo input. Si prega di riprovare."));
            return;
        }

        // If we have only one matches, complete the input
        if (count == 1) {
            heldItemID = matches.choiceNo[0] + 1;
            input = matches.name[0];
            return;
        }

        // If we have less than or equal to ten matches, populate a list keyboard
        if (count <= 10) {
            Keyboard kb;
            kb.CanAbort(false);
            kb.DisplayTopScreen = false;
            kb.Populate(matches.name);
            choice = kb.Open();

            if (choice >= 0) {
                heldItemID = matches.choiceNo[choice] + 1;
                input = matches.name[choice];
                return;
            }
        }

        // We have too much results, the user must keep typing letters
        keyboard.SetError(language("Too many results: ", "Trop de résultats: ", "Troppi risultati: ") + to_string(count) + language("\nType more letters to narrow down the results.", "\nEntrez plus de lettres pour affiner les résultats.", "\nDigita più lettere per restringere i risultati."));
    }

    void FindItemKB(MenuEntry *entry) {
        string output;

        if (KB<string>(language("Item:", "Objet tenu:", "Strumento"), true, 18, output, "", ItemInputChange))
            return;

        heldItemID = 0;
    }

    int moveID = 0;

    int MatchMove(Moves &output, string &input) {
        int index = 0;
        output.name.clear();
        string lowerCase(input);

        for (char &character : lowerCase)
            character = tolower(character);

        // Parse our possibilities to find the matches
        for (const string &moves : (currLang == Lang::ENG ? English::allMoves : French::allMoves)) {
            string::iterator iterator = lowerCase.begin();
            string::const_iterator itemIterator = moves.begin();

            // Parse every letter of input while it matches the move's name
            while (iterator != lowerCase.end() && itemIterator != moves.end() && *iterator == tolower(*itemIterator)) {
                ++iterator;
                ++itemIterator;
            }

            if (index < Helpers::AutoRegion(Helpers::GetVersion(617, 621), Helpers::GetVersion(719, 728))) {
                if (iterator == lowerCase.end()) {
                    output.name.push_back(moves);
                    output.choiceNo.push_back(index);
                }
            }

            index++;
        }

        return (output.choiceNo.size());
    }

    void MoveInputChange(Keyboard &keyboard, KeyboardEvent &event) {
        string &input = keyboard.GetInput();
        Moves matches;
        int count = MatchMove(matches, input);

        // If the user removed a letter, clear the input and set an error
        if (event.type == KeyboardEvent::CharacterRemoved) {
            input = "";
            keyboard.SetError(language("Type a letter to search for a move.", "Tapez une lettre pour chercher une attaque.", "Digitare una lettera per cercare un mossa."));
            return;
        }

         // Else if input's length is inferior than 3, ask for more letters
        else if (input.size() < 3) {
            keyboard.SetError(language("Not enough letters to do the search.","Pas assez de lettres pour effectuer la recherche.", "Non ci sono abbastanza lettere per effettuare la ricerca."));
            return;
        }

        // If we don't have any matches, tell the user
        if (!count) {
            keyboard.SetError(language("Nothing matches your input. Please try again.", "Rien ne correspond à votre saisie. Veuillez réessayer.", "Non c'è nulla che corrisponda al tuo input. Si prega di riprovare."));
            return;
        }

        // If we have only one matches, complete the input
        if (count == 1) {
            moveID = matches.choiceNo[0] + 1;
            OSD::Notify(Color::LimeGreen << language("Success", "Succès", "Successo") << Color::White << language("! Applied: ", "! Applied: ", "! Applicato: ") << matches.name[0]);
            keyboard.Close();
            return;
        }

        // If we have less than or equal to ten matches, populate a list keyboard
        if (count > 1 && count <= 10) {
            Keyboard kb(matches.name);
            kb.CanAbort(false);
            kb.DisplayTopScreen = false;
            int choice = kb.Open();

            if (choice >= 0) {
                moveID = matches.choiceNo[choice] + 1;
                OSD::Notify(Color::LimeGreen << language("Success", "Succès", "Successo") << Color::White << language("! Applied: ", "! Applied: ", "! Applicato: ") << matches.name[choice]);
                keyboard.Close();
                return;
            }
        }

        // We have too much results, the user must keep typing letters
        keyboard.SetError(language("Too many results: ", "Trop de résultats: ", "Troppi risultati: ") + to_string(count) + language("\nType more letters to narrow down the results.", "\nEntrez plus de lettres pour affiner les résultats.", "Digita più lettere per restringere i risultati."));
    }

    void FindMoveKB(MenuEntry *entry) {
        string output;

        if (KB<string>(language("Move:", "Attaque:", "Mossa"), true, 27, output, "", MoveInputChange))
            return;
    }
}