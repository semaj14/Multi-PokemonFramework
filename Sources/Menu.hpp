#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "stdafx.hpp"

#include "PlayerSearchSystem.hpp"
#include "FestivalPlaza.hpp"
#include "Battle.hpp"
#include "Trainer.hpp"
#include "Computer.hpp"
#include "Movement.hpp"
#include "Miscellaneous.hpp"

using namespace CTRPluginFramework;

void InitMenu(PluginMenu &menu) {
    string note = Color::Orange << "Note" << Color::White << ": ";

    MenuFolder *gts = new MenuFolder("Global Trade Station");
    *gts += new MenuEntry("Configuration", Helpers::ChooseEntry(PSS::GlobalTradeStation::Configuration, Plaza::GlobalTradeStation::Configuration), Helpers::ChooseEntry(PSS::GlobalTradeStation::ConfigurationKB, Plaza::GlobalTradeStation::ConfigurationKB), note + language("settings for depositing Pokémon.", "paramètres pour déposer des Pokémon."));
    *gts += new MenuEntry(language("Bypass 1 Deposit", "Contourner un dépôt"), Helpers::ChooseEntry(PSS::GlobalTradeStation::BypassLimit, Plaza::GlobalTradeStation::BypassLimit), note + language("there will no longer be a limit as to how much you may deposit.", "il n'y aura plus de limite quant à la quantité que vous pouvez déposer."));

    MenuFolder *plaza = new MenuFolder(language("Festival Plaza", "Place Festival"));
    *plaza += gts;
    *plaza += new MenuEntry(language("Current Rank", "Position actuelle"), nullptr, Plaza::CurrentRank);
    *plaza += new MenuEntry(language("FC Collected", "FP Collectés"), nullptr, Plaza::FCCollected);
    MenuFolder *records = new MenuFolder(language("Records", "Les enregistrements"));
    *records += new MenuEntry(language("Current FC", "FP acutels"), nullptr, Plaza::Profile::CurrentFC);
    *records += new MenuEntry(language("Guests Interacted With", "Invités avec qui vous avez interagi"), nullptr, Plaza::Profile::GuestsInteracted);
    *records += new MenuEntry(language("Facilities Hosted", "Installations accueillies"), nullptr, Plaza::Profile::FacilitiesHosted);
    *records += new MenuEntry(language("Missions Participated In", "Participation aux Missions"), nullptr, Plaza::Profile::MissionsParticipated);
    *plaza += records;
    *plaza += new MenuEntry(language("Image Crash Counter", "Compteur de plantages d'images"), Plaza::ImageCrashCounter);
    *plaza += new MenuEntry(language("Avoid Softban", "Éviter le bannissement temporaire"), Plaza::AvoidSoftban);

    MenuFolder *pss = new MenuFolder("Player Search System");
    *pss += gts;
    MenuFolder *profile = new MenuFolder(language("Profile", "Profil"));
    *profile += new MenuEntry(language("Icon", "Icône de profil"), nullptr, PSS::Profile::Icons);
    *profile += new MenuEntry(language("Nices", "Bravos"), nullptr, PSS::Profile::Nices);
    *profile += new MenuEntry(language("Wishes", "Anniversaires"), nullptr, PSS::Profile::Wishes);
    *profile += new MenuEntry("Message", nullptr, PSS::Profile::Message);
    *profile += new MenuEntry(language("History", "Historique d'activité"), nullptr, PSS::Profile::History);
    *profile += new MenuEntry(language("Location", "Lieu"), nullptr, PSS::Profile::Location);
    *profile += new MenuEntry("Links", nullptr, PSS::Profile::Links);
    *profile += new MenuEntry(language("Mini-Survey", "Mini-enquête"), nullptr, PSS::Profile::MiniSurvey);
    *profile += new MenuEntry(language("People Met", "Personnes rencontrées"), nullptr, PSS::Profile::Greets);
    *pss += profile;
    MenuFolder *opower = new MenuFolder(language("O-Power", "O-Aura"));
    *opower += new MenuEntry(language("Guage", "Jauge"), PSS::Guage, PSS::GuageKB);
    *opower += new MenuEntry(language("Unlock Every Power", "Débloquer tous les O-Auras"), nullptr, PSS::UnlockEveryPower);
    *pss += opower;
    *pss += new MenuEntry(language("Shout-Out", "Salutation"), nullptr, PSS::ShoutOut);
    *pss += new MenuEntry(language("Clear Users", "Effacer les personnes"), PSS::ClearUsers, PSS::ClearUsersKB, note + language("save the game and reload to apply the changes forever." , "enregistrez la partie et rechargez pour appliquer les changements de façon permanente."));
    *pss += new MenuEntry(language("Bypass Gift & Centre Icon", "Ignorer l'icône de cadeau et de centre"), PSS::BypassHackedIcons);
    menu += (group == Group::XY || group == Group::ORAS ? pss : plaza);

    MenuFolder *battle = new MenuFolder(language("Battle", "Combat"));
    MenuFolder *primary = new MenuFolder(language("Primary", "Principal"));

    *primary += new MenuFolder(language("Active", "En combat"), note + language("must be in a battle to use.", "doit être en combat pour être utilisé."), vector<MenuEntry*>({
        new MenuEntry(language("Slot: ", "Emplacement: ") << Color::Gray << "0", nullptr, Battle::Universal::SlotKB),
        new MenuEntry("Condition", nullptr, Battle::Universal::Condition),
        new MenuEntry(language("Statistics", "Statistiques"), Battle::Universal::Statistics, Battle::Universal::StatisticsKB),
        new MenuEntry(language("Invincibility", "Invincibilité"), Battle::Universal::Invincibility, Battle::Universal::InvincibilityKB),
        new MenuEntry(language("Item", "Objet tenu"), nullptr, Battle::Universal::Item),
        new MenuEntry(language("Attacks", "Attaques"), nullptr, Battle::Universal::Attacks),
        new MenuEntry(language("Exp. Multiplier", "Multiplicateur d'expérience"), Battle::Universal::ExpMultiplier, Battle::Universal::ExpMultiplierKB),
    }));

    *primary += EntryWithHotkey(new MenuEntry(language("Poké View", "Stats Pokémon"), nullptr, Battle::Universal::PokeView, note + language("press the following hotkey(s) below to see the other information. Be aware that this is experiemental for now.", "appuyez sur la (les) touche(s) de raccourci ci-dessous pour voir les autres informations. Notez que ceci est expérimental pour le moment.")), {Key::X, ""});
    *primary += EntryWithHotkey(new MenuEntry(language("Access Bag", "Accéder au sac"), Battle::Universal::AccessBag, note + language("hold the hotkey(s) below while pressing on an action when in a battle.", "maintenez la (les) touche(s) de raccourci ci-dessous tout en appuyant sur une action lorsque vous êtes en combat.")), {Key::R, ""});

    if (group == Group::XY || group == Group::ORAS)
        *primary += new MenuEntry(language("Bypass 1 Mega Restrict.", "Débloquer 1 restriction Méga"), Battle::Gen6::Bypass1MegaRestrict);

    if (group == Group::SM || group == Group::USUM) {
        *primary += new MenuEntry(language("Always Critical Hit", "Toujours un coup critique"), Battle::Gen7::AlwaysCriticalHit);
        *primary += new MenuEntry(language("Bypass 1 Mega Restrict.", "Débloquer 1 restriction Méga"), Battle::Gen7::Bypass1MegaRestrict);
        *primary += new MenuEntry(language("Infinite Z-Moves", "Z-Moves infinis"), Battle::Gen7::InfiniteZMoves);
        *primary += EntryWithHotkey(new MenuEntry(language("Z-Moves w/o Crystal", "Z-Moves sans cristal"), Battle::Gen7::ZMovesWithoutCrystal, note + language("activate before intiating a battle! When in battle, hold the hotkey(s) below while pressing on an action when in a battle.", "activez avant d'initier un combat ! En combat, maintenez la (les) touche(s) de raccourci ci-dessous tout en appuyant sur une action lorsque vous êtes en combat.")), {Key::L, ""});
    }

    if (group == Group::USUM)
        *primary += new MenuEntry(language("Ultra Burst w/o Ultranecrozium", "Rafale Ultra sans Ultranécrozélite"), Battle::Gen7::UltraBurst);

    *battle += primary;
    MenuFolder *other = new MenuFolder(language("Other", "Autre"));

    *other += new MenuFolder(language("Encounter", "Rencontre"), vector<MenuEntry*>({
        new MenuEntry(language("No Encounters", "Pas de rencontres"), Helpers::ChooseEntry(Battle::Gen6::NoEncounters, Battle::Gen7::NoEncounters)),
        new MenuEntry(language("Spawner", "Générateur"), nullptr, Helpers::ChooseEntry(Battle::Gen6::Spawner, Battle::Gen7::Spawner)),
        new MenuEntry(language("Shiny 100%", "Chromatique garantie"), Battle::Universal::Shiny100),
        new MenuEntry(language("Disable Shiny Lock", "Désactiver le Shiny Lock"), Battle::Universal::DisableShinyLock, note + language("this will allow you to remove the shiny not appearing setting on some Pokémon.", "cela vous permettra de supprimer le réglage empêchant l'apparition de chromatique pour certains Pokémon.")),
        new MenuEntry(language("Rematch Legendary", "Revancher contre un Pokémon légendaire"), nullptr, Helpers::ChooseEntry(Battle::Gen6::RematchLegendary, Battle::Gen7::RematchLegendary))
    }));

    if (group == Group::SM || group == Group::USUM) {
        *other += new MenuEntry(language("Re-fight Trainer", "Revancher contre un dresseur"), Battle::Gen7::RefightTrainer);
        *other += new MenuEntry(language("Reject Trainer Battle", "Refuser un combat contre un dresseur"), Battle::Gen7::RejectTrainerBattle);
    }

    *other += new MenuEntry(language("Guaranteed Catch", "Capture garantie"), Helpers::ChooseEntry(Battle::Gen6::GuaranteedCatch, Battle::Gen7::GuaranteedCatch));

    if (group == Group::SM || group == Group::USUM)
        *other += new MenuEntry(language("Can Catch Trial", "Peut capturer le Pokémon d'épreuve"), Battle::Gen7::CanCatchTrial);

    *other += new MenuEntry(language("Catch Trainer's Pokémon", "Attraper les Pokémon du dresseur"), Helpers::ChooseEntry(Battle::Gen6::CatchTrainersPokemon, Battle::Gen7::CatchTrainersPokemon));
    *battle += other;
    *battle += new MenuEntry(language("Music", "Musique"), nullptr, Battle::MusicKB);
    menu += battle;

    MenuFolder *trainer = new MenuFolder(language("Trainer", "Dresseur"));
    MenuFolder *info = new MenuFolder("Information");
    *info += new MenuEntry("IDs", nullptr, Trainer::Info::IDs, Helpers::AutoRegion<string>("", note + language("the ID that you see on your Pokémon is your TSV value.", "le code ID que vous voyez sur votre Pokémon correspond à votre valeur TSV.")));
    (group == Group::XY || group == Group::ORAS) ? *info += EntryWithHotkey(new MenuEntry(language("Name", "Nom"), Trainer::Info::CopyToName, Trainer::Info::Name, note + language("press the hotkey(s) below to copy the text from your shout-out to name.", "appuyez sur la ou les touches de raccourci ci-dessous pour copier le texte de votre message de salutation en tant que nom.")), {Key::Start | Key::A, ""}) : *info += new MenuEntry("Name", nullptr, Trainer::Info::Name);
    *info += new MenuEntry(language("Play Time", "Temps de jeu"), Trainer::Info::PlayTime, Trainer::Info::PlayTimeKB);
    *info += new MenuEntry(language("Language", "Langue"), Trainer::Info::Language, Trainer::Info::LanguageKB, note + language("save and restart to apply the changes.", "enregistrer et redémarrer pour appliquer les changements."));
    *trainer += info;
    MenuFolder *pouch = new MenuFolder(language("Pouch", "Sac"), note + language("these cheats will unlock every possible item within the game, and will be automatically sorted via ID number.", "ces triches débloqueront tous les objets possibles dans le jeu et seront automatiquement triés par numéro d'identification."));
    MenuFolder *currency = new MenuFolder(language("Currency", "Argent"));
    *currency += new MenuEntry(language("Money", "Pokédollars"), Trainer::Money, Trainer::MoneyKB);

    if (group == Group::XY || group == Group::ORAS)
        *currency += new MenuEntry("Poké Miles", Trainer::Gen6::PokeMiles, Trainer::Gen6::PokeMilesKB);

    *currency += new MenuEntry(language("Battle Points", "Points de Combat"), Trainer::BattlePoints, Trainer::BattlePointsKB);
    *pouch += currency;
    *pouch += new MenuEntry(language("Items", "Objets"), Trainer::Pouch::Items, Trainer::Pouch::ItemsKB);
    *pouch += new MenuEntry(language("Medicines", "Medicaments"), Trainer::Pouch::Medicines, Trainer::Pouch::MedicinesKB);
    *pouch += new MenuEntry(language("Berries", "Baies"), Trainer::Pouch::Berries, Trainer::Pouch::BerriesKB);
    *pouch += new MenuEntry(language("Unlockable", "Débloquables"), nullptr, Trainer::Pouch::Unlockable);
    *trainer += pouch;
    (group == Group::XY || group == Group::ORAS ? *trainer += new MenuEntry("Badges", nullptr, Trainer::Gen6::Badges) : *trainer += new MenuEntry("Z-Crystals", nullptr, Trainer::Gen7::ZCrystals));
    *trainer += new MenuEntry("Pokédex", nullptr, Trainer::Pokedex);
    menu += trainer;

    MenuFolder *computer = new MenuFolder(language("Computer", "PC"));
    *computer += new MenuEntry(language("Backup", "Sauvegarde"), nullptr, Computer::PCBackup);
    MenuFolder *editor = new MenuFolder(language("Editor", "Éditeur"));
    *editor += new MenuEntry(language("Setup", "Place du Pokémon"), nullptr, Computer::Editor::Initialize, note + language("this is to set up the Pokémon you would like to modify.", "ce paramètre permet de sélectionner le Pokémon que vous souhaitez modifier."));

    *editor += new MenuFolder(language("Main", "Principal"), vector<MenuEntry*>({
        new MenuEntry(language("Shiny", "Chromatique"), nullptr, Computer::Editor::Shinify),
        new MenuEntry(language("Species", "Espèce"), nullptr, Computer::Editor::Species),
        new MenuEntry(language("Is Nicknamed", "Surnommer"), nullptr, Computer::Editor::IsNicknamed),
        new MenuEntry(language("Nickname", "Surnom"), nullptr, Computer::Editor::Nickname),
        new MenuEntry(language("Level", "Niveau"), nullptr, Computer::Editor::Level),
        new MenuEntry("Nature", nullptr, Computer::Editor::Nature),
        new MenuEntry(language("Gender", "Genre"), nullptr, Computer::Editor::Gender),
        new MenuEntry(language("Form", "Forme"), nullptr, Computer::Editor::Form),
        new MenuEntry(language("Held Item", "Objet tenu"), nullptr, Computer::Editor::HeldItem),
        new MenuEntry(language("Ability", "Talent"), nullptr, Computer::Editor::Ability),
        new MenuEntry(language("Friendship", "Amitié"), nullptr, Computer::Editor::Friendship),
        new MenuEntry(language("Language", "Langue"), nullptr, Computer::Editor::Language),
        new MenuEntry(language("Is Egg", "Oeuf"), nullptr, Computer::Editor::IsEgg),
        new MenuEntry("Pokerus", nullptr, Computer::Editor::Pokerus),
        new MenuEntry(language("Country", "Pays"), nullptr, Computer::Editor::Country),
        new MenuEntry(language("Region", "Région"), nullptr),
        new MenuEntry(language("3DS Region", "Région 3DS"), nullptr, Computer::Editor::ConsoleRegion)
    }));

    *editor += new MenuFolder(language("Obtained", "Obtention"), vector<MenuEntry*>({
        new MenuEntry(language("Origin Game", "Jeu d'origine"), nullptr, Computer::Editor::OriginGame),
        new MenuEntry(language("Met Location", "Lieu de rencontre"), nullptr, Computer::Editor::MetLocation),
        new MenuEntry("Ball", nullptr, Computer::Editor::Ball),
        new MenuEntry(language("Met Level", "Niveau de rencontre"), nullptr, Computer::Editor::MetLevel),
        new MenuEntry(language("Met Date", "Date de rencontre"), nullptr, Computer::Editor::MetDate),
        new MenuEntry(language("Is Fateful Encounter", "Rencontre fatidique"), nullptr, Computer::Editor::IsFatefulEncounter),
        new MenuEntry(language("Egg Met Location", "Lieu de rencontre de l'œuf"), nullptr, Computer::Editor::EggMetLoc),
        new MenuEntry(language("Egg Met Date", "Date de rencontre de l'œuf"), nullptr, Computer::Editor::EggMetDate)
    }));

    *editor += new MenuFolder("Stats", vector<MenuEntry*>({
        new MenuEntry("IVs", nullptr, Computer::Editor::IVs),
        new MenuEntry("EVs", nullptr, Computer::Editor::EVs, note + language("keep in mind that there will be restrictions as to how much you can set per Pokémon.", "gardez à l'esprit qu'il y aura des restrictions quant à la quantité que vous pouvez définir par Pokémon.")),
        new MenuEntry(language("Contest", "Stats de concours"), nullptr, Computer::Editor::Contest)
    }));

    *editor += new MenuFolder(language("Attacks", "Attaques"), vector<MenuEntry*>({
        new MenuEntry(language("Current Moves", "Attaques actuelles"), nullptr, Computer::Editor::CurrentMoves),
        new MenuEntry(language("PP Ups", "PP Max"), nullptr, Computer::Editor::PPUps),
        new MenuEntry(language("Relearn Moves", "Capacités réapprises"), nullptr, Computer::Editor::RelearnMoves)
    }));

    *editor += new MenuFolder(language("Other", "Autre"), vector<MenuEntry*>({
        new MenuEntry("SID", nullptr, Computer::Editor::SID),
        new MenuEntry("TID", nullptr, Computer::Editor::TID),
        new MenuEntry(language("OT Name", "Nom DO"), nullptr, Computer::Editor::OTName),
        new MenuEntry(language("Latest (not OT) Handler", "Dernier dresseur"), nullptr, Computer::Editor::LatestHandler),
        new MenuEntry(language("Ribbons", "Rubans"), nullptr, Computer::Editor::Ribbons)
    }));

    *computer += editor;

    *computer += new MenuFolder(language("Cloning", "Clonage"), vector<MenuEntry*>({
        new MenuEntry(language("Custom", "Configuration"), nullptr, Computer::Cloning),
        EntryWithHotkey(new MenuEntry(language("Copy Pokémon in Trade", "Copier un Pokémon lors d'un échange"), Computer::CopyPokemonInTrade, note + language("this will overwrite any Pokémon sitting in slot 1 of box 1. If you understand, you may press on the following hotkeys.", "cela écrasera tout Pokémon dans la case 1 de la boîte 1. Si vous comprenez, vous pouvez appuyer sur les touches de raccourci suivantes.")), {Hotkey(Key::Start, "")}),
        new MenuEntry(language("Keep Original Pokémon", "Garder le Pokémon original"), Computer::KeepOriginalPokemon, Computer::KeepOriginalPokemonKB, note + language("the Pokémon will not be affected if moved, edited or replaced, it will still be there.", "le Pokémon ne sera pas affecté s'il est déplacé, édité ou remplacé, il restera toujours là."))
    }));

    *computer += new MenuEntry(language("PC Anywhere", "PC n'importe où"), Helpers::ChooseEntry(Computer::Gen6::PCAnywhere, Computer::Gen7::PCAnywhere), note + (group == Group::XY || group == Group::ORAS ? language("tap the settings icon on the bottom screen.", "appuyez sur l'icône des paramètres sur l'écran du bas.") : language("tap the settings icon from the in game menu screen.", "appuyez sur l'icône des paramètres à partir de l'écran de menu du jeu en cours.")));
    *computer += new MenuEntry(language("Unlock Every Box", "Débloquer toutes les boîtes"), nullptr, Computer::UnlockEveryBox);
    menu += computer;

    MenuFolder *movement = new MenuFolder(language("Movement", "Mouvement"));

    if (group == Group::XY || group == Group::ORAS) {
        MenuFolder *etc = new MenuFolder("Etc.");

        if (group == Group::ORAS)
            *etc += new MenuEntry(language("Model Swap", "Remplacement de modèle"), nullptr, Movement::Gen6::ORAS::ModelSwapKB);

        *etc += new MenuEntry(language("Action Music", "Musique d'action"), Movement::Gen6::ActionMusic, Movement::Gen6::ActionMusicKB);
        *etc += new MenuEntry(language("No Action Reset", "Réinitialisation sans action"), Movement::Gen6::NoActionReset);
        *etc += EntryWithHotkey(new MenuEntry(language("Teleportation", "Téléportation"), Movement::Gen6::Teleportation, Movement::Gen6::TeleportationKB, note + language("hold the hotkey(s) below while moving.", "maintenez la ou les touches de raccourci ci-dessous enfoncées tout en vous déplaçant.")), {Key::L, ""});
        *etc += new MenuEntry(language("Unlock Locations", "Débloquer les lieux"), nullptr, Movement::Gen6::UnlockLocations);
        *etc += new MenuEntry(language("Can Use Fly Anywhere", "Peut utiliser Vol n'importe où"), Movement::Gen6::CanUseFlyAnywhere, note + language("you must click on a Pokémon's summary through the 'X' menu in game.", "vous devez cliquer sur le résumé d'un Pokémon via le menu 'X' dans le jeu."));
        *movement += etc;
    }

    if (group == Group::SM || group == Group::USUM) {
        *movement += new MenuFolder("Etc.", vector<MenuEntry*>({
            new MenuEntry(language("Get All Mounts", "Avoir toutes les montures"), nullptr, Movement::Gen7::GetAllMounts, note + language("all mounts will be registered and unlocked despite not reaching a certain point of the story.", "tous les montures seront enregistrées et déverrouillées même si vous n'avez pas atteint un certain point de l'histoire.")),
            EntryWithHotkey(new MenuEntry(language("Camera Zoom Out", "Zoom arrière de la caméra"), Movement::Gen7::CameraZoomOut), {Hotkey(Key::L, language("Zoom-Out", "Dézoomer")), Hotkey(Key::R, language("Zoom-In", "Zoom avant"))}),
            new MenuEntry(language("Remove Player Shadow", "Supprimer l'ombre du joueur"), Movement::Gen7::RemovePlayerShadow)
        }));
    }

    *movement += new MenuEntry(language("Speed Up", "Aller plus vite"), Helpers::ChooseEntry(Movement::Gen6::SpeedUp, Movement::Gen7::SpeedUp), note + language("only applies to walk and run speeds, and works with D-Pad.", "cela s'applique uniquement aux vitesses de marche et de course, et fonctionne avec la croix directionnelle."));
    *movement += new MenuEntry(language("Bypass Walls", "Passer à travers les murs"), Helpers::ChooseEntry(Movement::Gen6::BypassWalls, Movement::Gen7::BypassWalls));

    if (group == Group::SM || group == Group::USUM)
        *movement += new MenuEntry(language("Time of Day", "Heure du jour"), nullptr, Movement::Gen7::TimeOfDay);

    menu += movement;

    MenuFolder *misc = new MenuFolder(language("Miscellaneous", "Divers"));

    if (group == Group::ORAS)
        *misc += new MenuEntry(language("Weather", "Météo"), Misc::Weather, Misc::WeatherKB);

    MenuFolder *pokemon = new MenuFolder("Pokémon");
    *pokemon += new MenuEntry(language("Is Renamable", "Est renommable"), Misc::IsRenamable, note + language("you will be able to rename any Pokémon despite it not being at your ownership.", "vous pourrez renommer n'importe quel Pokémon même s'il n'est pas en votre possession."));
    *pokemon += new MenuEntry(language("Learn Any Teachables", "Apprendre tous les apprenables"), Misc::LearnAnyTeachables, note + language("you will be able to teach your Pokémon any moves.", "vous pourrez apprendre n'importe quelle attaque à vos Pokémon."));
    *pokemon += new MenuEntry(language("Get Day Care Egg", "Obtenir un oeuf de la Pension"), Misc::GetDayCareEgg);
    *pokemon += new MenuEntry(language("Instant Egg Hatch", "Éclosion instantanée d'œuf"), Helpers::ChooseEntry(Misc::Gen6::InstantEggHatch, Misc::Gen7::InstantEggHatch));

    *pokemon += new MenuFolder(language("Other", "Autre"), vector<MenuEntry*>({
        EntryWithHotkey(new MenuEntry(language("View Values in Summary", "Voir les valeurs dans le résumé"), Helpers::ChooseEntry(Misc::Gen6::ViewValuesInSummary, Misc::Gen7::ViewValuesInSummary), note + language("hold one of the following hotkey(s) to view your Individual and Effort Values.", "maintenez l'une des touches de raccourci suivantes pour afficher vos valeurs individuelles et d'effort.")), {Hotkey(Key::L, ""), Hotkey(Key::R, "")})
    }));

    *misc += pokemon;
    *misc += new MenuEntry(language("Remove Outlines", "Supprimer les contours"), Helpers::ChooseEntry(Misc::Gen6::NoOutlines, Misc::Gen7::NoOutlines), note + language("removes outlines in the overworld and in battles.", "supprime les contours dans le monde extérieur et pendant les combats."));
    *misc += new MenuEntry(language("Fast Dialogs", "Dialogues rapides"), Misc::FastDialogs, note + language("game dialogs will be sped up.", "les dialogues du jeu seront accélérés."));
    *misc += new MenuEntry(language("Bypass Text Restricts.", "Dépasser les restrictions de texte"), Misc::BypassTextRestricts);

    if ((group == Group::XY || group == Group::ORAS)) {
        *misc += new MenuFolder(language("Custom Game Keyboard", "Clavier personnalisé du jeu"), vector<MenuEntry*>({
            new MenuEntry("Config", nullptr, Misc::CustomKeyboardConfig, note + language("for the in-game keyboard only. This overrides the 'More' section. Make sure to backup your customized keyboards so you won't have to re-enter the values.", "pour le clavier intégré au jeu. Cela remplace la section 'Plus'. Assurez-vous de sauvegarder vos claviers personnalisés afin de ne pas avoir à saisir à nouveau les valeurs.")),
            EntryWithHotkey(new MenuEntry(language("Keys", "Les touches"), Misc::CustomKeys, note + language("press the hotkey(s) below to customize the keys. Press Y to clear keyboard. Accepting unicode values only, can be found elsewhere.", "appuyez sur la ou les touches de raccourci ci-dessous pour personnaliser les touches. Appuyez sur Y pour effacer le clavier. Accepte uniquement les valeurs unicode, qui peuvent être trouvées ailleurs.")), {Hotkey(Key::X, "")})
        }));

        *misc += new MenuEntry(language("Patch Colored Text Crashes", "Corriger les plantages liés aux textes en couleur"), Misc::PatchColorCrash);
    }

    menu += misc;

    menu += new MenuEntry(language("Settings", "Menu des préférences"), nullptr, Settings, note + language("resetting your settings will launch you straight back to the home menu, remember to save your game before doing so.", "réinitialiser vos paramètres vous ramènera directement au menu principal, n'oubliez pas de sauvegarder votre jeu avant de le faire."));
}