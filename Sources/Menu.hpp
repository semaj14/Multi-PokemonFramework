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
    string note = Color::Orange << language("Note", "Note", "Nota") << Color::White << ": ";

    MenuFolder *gts = new MenuFolder("Global Trade Station");
    *gts += new MenuEntry(language("Configuration", "Configuration", "Criteri GTS"), Helpers::ChooseEntry(PSS::GlobalTradeStation::Configuration, Plaza::GlobalTradeStation::Configuration), Helpers::ChooseEntry(PSS::GlobalTradeStation::ConfigurationKB, Plaza::GlobalTradeStation::ConfigurationKB), note + language("settings for depositing Pokémon.", "paramètres pour déposer des Pokémon.", "impostazioni per il deposito dei Pokémon."));
    *gts += new MenuEntry(language("Bypass 1 Deposit", "Contourner un dépôt", "Deposita più Pokémon"), Helpers::ChooseEntry(PSS::GlobalTradeStation::BypassLimit, Plaza::GlobalTradeStation::BypassLimit), note + language("there will no longer be a limit as to how much you may deposit.", "il n'y aura plus de limite quant à la quantité que vous pouvez déposer.", "non ci sarà più un limite su quanti Pokémon puoi depositare nel GTS."));

    MenuFolder *plaza = new MenuFolder(language("Festival Plaza", "Place Festival", "Festiplaza"));
    *plaza += gts;
    *plaza += new MenuEntry(language("Current Rank", "Position actuelle", "Livello"), nullptr, Plaza::CurrentRank);
    *plaza += new MenuEntry(language("FC Collected", "FP Collectés", "Festigettoni ottenuti in totale"), nullptr, Plaza::FCCollected);
    MenuFolder *records = new MenuFolder(language("Records", "Les enregistrements", "Dati Festiplaza"));
    *records += new MenuEntry(language("Current FC", "FP acutels", "Festigettoni disponibili"), nullptr, Plaza::Profile::CurrentFC);
    *records += new MenuEntry(language("Guests Interacted With", "Invités avec qui vous avez interagi", "Ospiti incontrati"), nullptr, Plaza::Profile::GuestsInteracted);
    *records += new MenuEntry(language("Facilities Hosted", "Installations accueillies", "Strutture inaugurate"), nullptr, Plaza::Profile::FacilitiesHosted);
    *records += new MenuEntry(language("Missions Participated In", "Participation aux Missions", "Partite ai minigiochi"), nullptr, Plaza::Profile::MissionsParticipated);
    *plaza += records;
    *plaza += new MenuEntry(language("Image Crash Counter", "Compteur de plantages d'images", "Fix freeze GTS"), Plaza::ImageCrashCounter);
    *plaza += new MenuEntry(language("Avoid Softban", "Éviter le bannissement temporaire", "Evita divieti temporanei"), Plaza::AvoidSoftban);

    MenuFolder *pss = new MenuFolder("Player Search System");
    *pss += gts;
    MenuFolder *profile = new MenuFolder(language("Profile", "Profil", "Profilo"));
    *profile += new MenuEntry(language("Icon", "Icône de profil", "Icona del profilo"), nullptr, PSS::Profile::Icons);
    *profile += new MenuEntry(language("Nices", "Bravos", "WOW"), nullptr, PSS::Profile::Nices);
    *profile += new MenuEntry(language("Wishes", "Anniversaires", "Auguri"), nullptr, PSS::Profile::Wishes);
    *profile += new MenuEntry(language("Message", "Message", "Messaggio"), nullptr, PSS::Profile::Message);
    *profile += new MenuEntry(language("History", "Historique d'activité", "Attività svolte"), nullptr, PSS::Profile::History);
    *profile += new MenuEntry(language("Location", "Lieu", "Collegamenti"), nullptr, PSS::Profile::Location);
    *profile += new MenuEntry("Links", nullptr, PSS::Profile::Links);
    *profile += new MenuEntry(language("Mini-Survey", "Mini-Enquête", "Mini-Sondaggi"), nullptr, PSS::Profile::MiniSurvey);
    *profile += new MenuEntry(language("People Met", "Personnes rencontrées", "Persone incontrate"), nullptr, PSS::Profile::Greets);
    *pss += profile;
    MenuFolder *opower = new MenuFolder(language("O-Power", "O-Aura", "Poteri O"));
    *opower += new MenuEntry(language("Guage", "Jauge", "Punti energia"), PSS::Guage, PSS::GuageKB);
    *opower += new MenuEntry(language("Unlock Every Power", "Débloquer tous les O-Auras", "Ottieni tutti i Poteri O"), nullptr, PSS::UnlockEveryPower);
    *pss += opower;
    *pss += new MenuEntry(language("Shout-Out", "Salutation", "Firmallegra"), nullptr, PSS::ShoutOut);
    *pss += new MenuEntry(language("Clear Users", "Effacer les personnes", "Rimuovi passanti"), PSS::ClearUsers, PSS::ClearUsersKB, note + language("save the game and reload to apply the changes forever.", "enregistrez la partie et rechargez pour appliquer les changements de façon permanente.", "salvare il gioco e ricaricarlo per applicare le modifiche per sempre."));
    *pss += new MenuEntry(language("Bypass Gift & Centre Icon", "Ignorer l'icône de cadeau et de centre", "Ignora le icone Regalo e Centro Pokémon"), PSS::BypassHackedIcons);
    menu += (group == Group::XY || group == Group::ORAS ? pss : plaza);

    MenuFolder *battle = new MenuFolder(language("Battle", "Combat", "Battaglia"));
    MenuFolder *primary = new MenuFolder(language("Primary", "Principal", "Primario"));

    *primary += new MenuFolder(language("Active", "En combat", "In battaglia"), note + language("must be in a battle to use.", "doit être en combat pour être utilisé.", "devi essere in combattimento per utilizzare questi trucchi."), vector<MenuEntry*>({
        new MenuEntry(language("Slot: ", "Emplacement: ", "Slot: ") << Color::Gray << "0", nullptr, Battle::Universal::SlotKB),
        new MenuEntry(language("Condition", "Condition", "Problemi di Stato"), nullptr, Battle::Universal::Condition),
        new MenuEntry(language("Statistics", "Statistiques", "Statistiche"), Battle::Universal::Statistics, Battle::Universal::StatisticsKB),
        new MenuEntry(language("Invincibility", "Invincibilité", "Invincibilità"), Battle::Universal::Invincibility, Battle::Universal::InvincibilityKB),
        new MenuEntry(language("Item", "Objet tenu", "Strumento tenuto"), nullptr, Battle::Universal::Item),
        new MenuEntry(language("Attacks", "Attaques", "Mosse"), nullptr, Battle::Universal::Attacks),
        new MenuEntry(language("Exp. Multiplier", "Multiplicateur d'expérience", "Moltiplicatore di Esperienza"), Battle::Universal::ExpMultiplier, Battle::Universal::ExpMultiplierKB),
    }));

    *primary += EntryWithHotkey(new MenuEntry(language("Poké View", "Stats Pokémon", "Informazioni Pokémon avversario"), nullptr, Battle::Universal::PokeView, note + language("press the following hotkey(s) below to see the other information. Be aware that this is experiemental for now.", "appuyez sur la (les) touche(s) de raccourci ci-dessous pour voir les autres informations. Notez que ceci est expérimental pour le moment.", "premi il tasto di scelta rapida per visualizzare le altre informazioni. Tieni presente che per il momento si tratta di una funzione sperimentale.")), {Key::X, ""});
    *primary += EntryWithHotkey(new MenuEntry(language("Access Bag", "Accéder au sac", "Accedi alla borsa"), Battle::Universal::AccessBag, note + language("hold the hotkey(s) below while pressing on an action when in a battle.", "maintenez la (les) touche(s) de raccourci ci-dessous tout en appuyant sur une action lorsque vous êtes en combat.", "Tieni premuto il tasto di scelta rapida mentre clicchi un bottone qualsiasi nel menu battaglia.")), {Key::R, ""});

    if (group == Group::XY || group == Group::ORAS)
        *primary += new MenuEntry(language("Bypass 1 Mega Restrict", "Débloquer 1 restriction Méga", "Rimuovi restrizione Megaevoluzione"), Battle::Gen6::Bypass1MegaRestrict);

    if (group == Group::SM || group == Group::USUM) {
        *primary += new MenuEntry(language("Always Critical Hit", "Toujours un coup critique", "Colpo sempre Critico"), Battle::Gen7::AlwaysCriticalHit);
        *primary += new MenuEntry(language("Bypass 1 Mega Restrict.", "Débloquer 1 restriction Méga", "Rimuovi restrizione Megaevoluzione"), Battle::Gen7::Bypass1MegaRestrict);
        *primary += new MenuEntry(language("Infinite Z-Moves", "Z-Moves infinis", "Mossa Z infinite"), Battle::Gen7::InfiniteZMoves);
        *primary += EntryWithHotkey(new MenuEntry(language("Z-Moves w/o Crystal", "Z-Moves sans cristal", "Mosse Z senza Cristalli Z"), Battle::Gen7::ZMovesWithoutCrystal, note + language("activate before intiating a battle! When in battle, hold the hotkey(s) below while pressing on an action when in a battle.", "activez avant d'initier un combat ! En combat, maintenez la (les) touche(s) de raccourci ci-dessous tout en appuyant sur une action lorsque vous êtes en combat.", "attivare prima di iniziare una battaglia. Quando si è in battaglia, tieni premuto il tasto di scelta rapida sotto riportato mentre clicchi il tasto Lotta")), {Key::L, ""});
    }

    if (group == Group::USUM)
        *primary += new MenuEntry(language("Ultra Burst w/o Ultranecrozium", "Rafale Ultra sans Ultranécrozélite", "Ultraesplosione senza Ultranecrozium Z"), Battle::Gen7::UltraBurst);

    *battle += primary;
    MenuFolder *other = new MenuFolder(language("Other", "Autre", "Altro"));

    *other += new MenuFolder(language("Encounter", "Rencontre", "Incontro"), vector<MenuEntry*>({
        new MenuEntry(language("No Encounters", "Pas de rencontres", "Blocca incontri"), Helpers::ChooseEntry(Battle::Gen6::NoEncounters, Battle::Gen7::NoEncounters)),
        new MenuEntry(language("Spawner", "Générateur", "Selvatico specifico"), nullptr, Helpers::ChooseEntry(Battle::Gen6::Spawner, Battle::Gen7::Spawner)),
        new MenuEntry(language("Shiny 100%", "Chromatique garantie", "100% cromatico"), Battle::Universal::Shiny100),
        new MenuEntry(language("Disable Shiny Lock", "Désactiver le Shiny Lock", "Disabilita Shiny Lock"), Battle::Universal::DisableShinyLock, note + language("this will allow you to remove the shiny not appearing setting on some Pokémon.", "cela vous permettra de supprimer le réglage empêchant l'apparition de chromatique pour certains Pokémon.", "questo trucco rimuove lo Shiny Lock, quindi potrai trovare qualsiasi Pokémon nella sua forma cromatica.")),
        new MenuEntry(language("Rematch Legendary", "Revancher contre un Pokémon légendaire", "Riaffronta i Leggendari"), nullptr, Helpers::ChooseEntry(Battle::Gen6::RematchLegendary, Battle::Gen7::RematchLegendary))
    }));

    if (group == Group::SM || group == Group::USUM) {
        *other += new MenuEntry(language("Re-fight Trainer", "Revancher contre un dresseur", "Riaffronta gli Allenatori"), Battle::Gen7::RefightTrainer);
        *other += new MenuEntry(language("Reject Trainer Battle", "Refuser un combat contre un dresseur", "Ignora le sfide degli Allenatori"), Battle::Gen7::RejectTrainerBattle);
    }

    *other += new MenuEntry(language("Guaranteed Catch", "Capture garantie", "Cattura garantita"), Helpers::ChooseEntry(Battle::Gen6::GuaranteedCatch, Battle::Gen7::GuaranteedCatch));

    if (group == Group::SM || group == Group::USUM)
        *other += new MenuEntry(language("Can Catch Trial", "Peut capturer le Pokémon d'épreuve", "Puoi catturare i Pokémon delle prove"), Battle::Gen7::CanCatchTrial);

    *other += new MenuEntry(language("Catch Trainer's Pokémon", "Attraper les Pokémon du dresseur", "Catturare i Pokémon degli Allenatori"), Helpers::ChooseEntry(Battle::Gen6::CatchTrainersPokemon, Battle::Gen7::CatchTrainersPokemon));
    *battle += other;
    *battle += new MenuEntry(language("Music", "Musique", "Musica"), nullptr, Battle::MusicKB);
    menu += battle;

    MenuFolder *trainer = new MenuFolder(language("Trainer", "Dresseur", "Allenatore"));
    MenuFolder *info = new MenuFolder(language("Information", "Information", "Informazioni Allenatore"));
    *info += new MenuEntry(language("IDs", "IDs", "Cambia gli ID"), nullptr, Trainer::Info::IDs, Helpers::AutoRegion<string>("", note + language("the ID that you see on your Pokémon is your TSV value.", "le code ID que vous voyez sur votre Pokémon correspond à votre valeur TSV.", "l'ID che vedete sul vostro Pokémon è il vostro ID Allenatore.")));
    (group == Group::XY || group == Group::ORAS) ? *info += EntryWithHotkey(new MenuEntry(language("Name", "Nom", "Nome"), Trainer::Info::CopyToName, Trainer::Info::Name, note + language("press the hotkey(s) below to copy the text from your shout-out to name.", "appuyez sur la ou les touches de raccourci ci-dessous pour copier le texte de votre message de salutation en tant que nom.", "premi i tasti di scelta rapida sottostanti per copiare la tua Firmallegra e impostarla come Nome.")), {Key::Start | Key::A, ""}) : *info += new MenuEntry(language("Name", "Name", "Nome"), nullptr, Trainer::Info::Name);
    *info += new MenuEntry(language("Play Time", "Temps de jeu", "Tempo di gioco"), Trainer::Info::PlayTime, Trainer::Info::PlayTimeKB);
    *info += new MenuEntry(language("Language", "Langue", "Lingua"), Trainer::Info::Language, Trainer::Info::LanguageKB, note + language("save and restart to apply the changes.", "enregistrer et redémarrer pour appliquer les changements.", "salva e riavvia per applicare le modifiche."));
    *trainer += info;
    MenuFolder *pouch = new MenuFolder(language("Pouch", "Sac", "Borsa"), note + language("these cheats will unlock every possible item within the game, and will be automatically sorted via ID number.", "ces triches débloqueront tous les objets possibles dans le jeu et seront automatiquement triés par numéro d'identification.", "questi trucchi sbloccheranno ogni possibile oggetto all'interno del gioco e verranno automaticamente ordinati tramite numero ID."));
    MenuFolder *currency = new MenuFolder(language("Currency", "Argent", "Valute"));
    *currency += new MenuEntry(language("Money", "Pokédollars", "Soldi"), Trainer::Money, Trainer::MoneyKB);

    if (group == Group::XY || group == Group::ORAS)
        *currency += new MenuEntry(language("Poké Miles", "Poké Miles", "Pokèmiglia"), Trainer::Gen6::PokeMiles, Trainer::Gen6::PokeMilesKB);

    *currency += new MenuEntry(language("Battle Points", "Points de Combat", "Punti Lotta"), Trainer::BattlePoints, Trainer::BattlePointsKB);
    *pouch += currency;
    *pouch += new MenuEntry(language("Items", "Objets", "Strumenti"), Trainer::Pouch::Items, Trainer::Pouch::ItemsKB);
    *pouch += new MenuEntry(language("Medicines", "Medicaments", "Rimedi"), Trainer::Pouch::Medicines, Trainer::Pouch::MedicinesKB);
    *pouch += new MenuEntry(language("Berries", "Baies", "Bacche"), Trainer::Pouch::Berries, Trainer::Pouch::BerriesKB);
    *pouch += new MenuEntry(language("Unlockable", "Débloquables", "Ottieni"), nullptr, Trainer::Pouch::Unlockable);
    *trainer += pouch;
    (group == Group::XY || group == Group::ORAS ? *trainer += new MenuEntry(language("Badges", "Badges", "Medaglie"), nullptr, Trainer::Gen6::Badges) : *trainer += new MenuEntry(language("Z-Crystals", "Z-Crystals", "Cristalli Z"), nullptr, Trainer::Gen7::ZCrystals));
    *trainer += new MenuEntry("Pokédex", nullptr, Trainer::Pokedex);
    menu += trainer;

    MenuFolder *computer = new MenuFolder(language("Computer", "PC", "PC"));
    *computer += new MenuEntry(language("Backup", "Sauvegarde", "Backup"), nullptr, Computer::PCBackup);
    MenuFolder *editor = new MenuFolder(language("Editor", "Éditeur", "Editor"));
    *editor += new MenuEntry(language("Setup", "Place du Pokémon", "Posizione del Pokémon"), nullptr, Computer::Editor::Initialize, note + language("this is to set up the Pokémon you would like to modify.", "ce paramètre permet de sélectionner le Pokémon que vous souhaitez modifier.", "questo serve per impostare il Pokémon che desideri modificare."));

    *editor += new MenuFolder(language("Main", "Principal", "Principale"), vector<MenuEntry*>({
        new MenuEntry(language("Shiny", "Chromatique", "Cromatico?"), nullptr, Computer::Editor::Shinify),
        new MenuEntry(language("Species", "Espèce", "Specie"), nullptr, Computer::Editor::Species),
        new MenuEntry(language("Is Nicknamed", "Surnommer", "È soprannominato?"), nullptr, Computer::Editor::IsNicknamed),
        new MenuEntry(language("Nickname", "Surnom", "Soprannome"), nullptr, Computer::Editor::Nickname),
        new MenuEntry(language("Level", "Niveau", "Livello"), nullptr, Computer::Editor::Level),
        new MenuEntry(language("Nature", "Nature", "Natura"), nullptr, Computer::Editor::Nature),
        new MenuEntry(language("Gender", "Genre", "Sesso"), nullptr, Computer::Editor::Gender),
        new MenuEntry(language("Form", "Forme", "Forma"), nullptr, Computer::Editor::Form),
        new MenuEntry(language("Held Item", "Objet tenu", "Strumento tenuto"), nullptr, Computer::Editor::HeldItem),
        new MenuEntry(language("Ability", "Talent", "Abilità"), nullptr, Computer::Editor::Ability),
        new MenuEntry(language("Friendship", "Amitié", "Livello amicizia"), nullptr, Computer::Editor::Friendship),
        new MenuEntry(language("Language", "Langue", "Lingua"), nullptr, Computer::Editor::Language),
        new MenuEntry(language("Is Egg", "Oeuf", "È un uovo?"), nullptr, Computer::Editor::IsEgg),
        new MenuEntry("Pokérus", nullptr, Computer::Editor::Pokerus),
        new MenuEntry(language("Country", "Pays", "Paese"), nullptr, Computer::Editor::Country),
        new MenuEntry(language("Region", "Région", "Sottoregione"), nullptr),
        new MenuEntry(language("3DS Region", "Région 3DS", "Regione 3DS"), nullptr, Computer::Editor::ConsoleRegion)
    }));

    *editor += new MenuFolder(language("Obtained", "Obtention", "Ottenuto"), vector<MenuEntry*>({
        new MenuEntry(language("Origin Game", "Jeu d'origine", "Gioco di origine"), nullptr, Computer::Editor::OriginGame),
        new MenuEntry(language("Met Location", "Lieu de rencontre", "Provenienza"), nullptr, Computer::Editor::MetLocation),
        new MenuEntry(language("Ball", "Ball", "Poké Ball"), nullptr, Computer::Editor::Ball),
        new MenuEntry(language("Met Level", "Niveau de rencontre", "Livello di incontro"), nullptr, Computer::Editor::MetLevel),
        new MenuEntry(language("Met Date", "Date de rencontre", "Data di incontro"), nullptr, Computer::Editor::MetDate),
        new MenuEntry(language("Is Fateful Encounter", "Rencontre fatidique", "Evento speciale?"), nullptr, Computer::Editor::IsFatefulEncounter),
        new MenuEntry(language("Egg Met Location", "Lieu de rencontre de l'œuf", "Luogo ottenimento uovo"), nullptr, Computer::Editor::EggMetLoc),
        new MenuEntry(language("Egg Met Date", "Date de rencontre de l'œuf", "Data ottenimento uovo"), nullptr, Computer::Editor::EggMetDate)
    }));

    *editor += new MenuFolder(language("Stats", "Stats", "Statistiche"), vector<MenuEntry*>({
        new MenuEntry(language("IVs", "IVs", "IV"), nullptr, Computer::Editor::IVs),
        new MenuEntry(language("EVs", "EVs", "EV"), nullptr, Computer::Editor::EVs, note + language("keep in mind that there will be restrictions as to how much you can set per Pokémon.", "gardez à l'esprit qu'il y aura des restrictions quant à la quantité que vous pouvez définir par Pokémon.", "Tieni presente che ci sono delle limitazione per quanto riguarda i punti che potrai impostare.")),
        new MenuEntry(language("Contest", "Stats de concours", "Statistiche gare"), nullptr, Computer::Editor::Contest)
    }));

    *editor += new MenuFolder(language("Attacks", "Attaques", "Modifica mosse"), vector<MenuEntry*>({
        new MenuEntry(language("Current Moves", "Attaques actuelles", "Mosse"), nullptr, Computer::Editor::CurrentMoves),
        new MenuEntry(language("PP Ups", "PP Max", "Modifica Punti Potenza"), nullptr, Computer::Editor::PPUps),
        new MenuEntry(language("Relearn Moves", "Capacités réapprises", "Ricordamosse"), nullptr, Computer::Editor::RelearnMoves)
    }));

    *editor += new MenuFolder(language("Other", "Autre", "Altro"), vector<MenuEntry*>({
        new MenuEntry(language("SID", "SID", "ID Segreto"), nullptr, Computer::Editor::SID),
        new MenuEntry(language("TID", "TID", "ID Allenatore"),nullptr, Computer::Editor::TID),
        new MenuEntry(language("OT Name", "Nom DO", "Nome Allenatore originale"), nullptr, Computer::Editor::OTName),
        new MenuEntry(language("Latest (not OT) Handler", "Dernier dresseur", "Ultimo Allenatore"), nullptr, Computer::Editor::LatestHandler),
        new MenuEntry(language("Ribbons", "Rubans", "Fiocchi"), nullptr, Computer::Editor::Ribbons)
    }));

    *computer += editor;

    *computer += new MenuFolder(language("Cloning", "Clonage", "Clona"), vector<MenuEntry*>({
        new MenuEntry(language("Custom", "Configuration", "Configurazione"), nullptr, Computer::Cloning),
        EntryWithHotkey(new MenuEntry(language("Copy Pokémon in Trade", "Copier un Pokémon lors d'un échange", "Copia i Pokémon in Scambio"), Computer::CopyPokemonInTrade, note + language("this will overwrite any Pokémon sitting in slot 1 of box 1. If you understand, you may press on the following hotkeys.", "cela écrasera tout Pokémon dans la case 1 de la boîte 1. Si vous comprenez, vous pouvez appuyer sur les touches de raccourci suivantes.", "questo trucco sovrascriverà il Pokémon che si trova nello Slot 1 del Box 1. Se hai capito, puoi premere i tasti di scelta rapida.")), {Hotkey(Key::Start, "")}),
        new MenuEntry(language("Keep Original Pokémon", "Garder le Pokémon original", "Conservare il Pokémon originale"), Computer::KeepOriginalPokemon, Computer::KeepOriginalPokemonKB, note + language("the Pokémon will not be affected if moved, edited or replaced, it will still be there.", "le Pokémon ne sera pas affecté s'il est déplacé, édité ou remplacé, il restera toujours là.", "il Pokémon non sarà influenzato se viene spostato, modificato o sostituito, sarà ancora lì."))
    }));

    *computer += new MenuEntry(language("PC Anywhere", "PC n'importe où", "Apri il PC ovunque"), Helpers::ChooseEntry(Computer::Gen6::PCAnywhere, Computer::Gen7::PCAnywhere), note + (group == Group::XY || group == Group::ORAS ? language("tap the settings icon on the bottom screen.", "appuyez sur l'icône des paramètres sur l'écran du bas.", "tocca l'icona Impostazione nello schermo inferiore.") : language("tap the settings icon from the in game menu screen.", "appuyez sur l'icône des paramètres à partir de l'écran de menu du jeu en cours.", "tocca l'icona Impostazioni nella schermata del menu di gioco.")));
    *computer += new MenuEntry(language("Unlock Every Box", "Débloquer toutes les boîtes", "Sblocca tutti i Box"), nullptr, Computer::UnlockEveryBox);
    menu += computer;

    MenuFolder *movement = new MenuFolder(language("Movement", "Mouvement", "Movimento"));

    if (group == Group::XY || group == Group::ORAS) {
        MenuFolder *etc = new MenuFolder(language("Etc.", "Etc.", "Altro"));

        if (group == Group::ORAS)
            *etc += new MenuEntry(language("Model Swap", "Remplacement de modèle", "Cambia modello"), nullptr, Movement::Gen6::ORAS::ModelSwapKB);

        *etc += new MenuEntry(language("Action Music", "Musique d'action", "Musica di sottofondo"), Movement::Gen6::ActionMusic, Movement::Gen6::ActionMusicKB);
        *etc += new MenuEntry(language("No Action Reset", "Réinitialisation sans action", "Nessun ripristino azione"), Movement::Gen6::NoActionReset);
        *etc += EntryWithHotkey(new MenuEntry(language("Teleportation", "Téléportation", "Teletrasporto"), Movement::Gen6::Teleportation, Movement::Gen6::TeleportationKB, note + language("hold the hotkey(s) below while moving.", "maintenez la ou les touches de raccourci ci-dessous enfoncées tout en vous déplaçant.", "premi il tasto di scelta rapida mentre entri in un edificio.")), {Key::L, ""});
        *etc += new MenuEntry(language("Unlock Locations", "Débloquer les lieux", "Sblocca tutte le zone"), nullptr, Movement::Gen6::UnlockLocations);
        *etc += new MenuEntry(language("Can Use Fly Anywhere", "Peut utiliser Vol n'importe où", "Puoi usare Volo ovunque"), Movement::Gen6::CanUseFlyAnywhere, note + language("you must click on a Pokémon's summary through the 'X' menu in game.", "vous devez cliquer sur le résumé d'un Pokémon via le menu 'X' dans le jeu.", "basta che clicchi il bottone Info di un qualsiasi Pokémon che si trova nella nella tua squadra."));
        *movement += etc;
    }

    if (group == Group::SM || group == Group::USUM) {
        *movement += new MenuFolder(language("Etc.", "Etc.", "Altro"), vector<MenuEntry*>({
            new MenuEntry(language("Get All Mounts", "Avoir toutes les montures", "Ottieni tutti i Chiamapassaggio"), nullptr, Movement::Gen7::GetAllMounts, note + language("all mounts will be registered and unlocked despite not reaching a certain point of the story.", "tous les montures seront enregistrées et déverrouillées même si vous n'avez pas atteint un certain point de l'histoire.", "tutti i Chiamapassaggio saranno registrati e sbloccati nonostante non si sia raggiunto un determinato punto della storia.")),
            EntryWithHotkey(new MenuEntry(language("Camera Zoom Out", "Zoom arrière de la caméra", "Cambia Zoom"), Movement::Gen7::CameraZoomOut), {Hotkey(Key::L, language("Zoom-Out", "Dézoomer", "Diminuire zoom")), Hotkey(Key::R, language("Zoom-In", "Zoom avant", "Aumentare lo zoom"))}),
            new MenuEntry(language("Remove Player Shadow", "Supprimer l'ombre du joueur", "Rimuovi l'ombra del giocatore"), Movement::Gen7::RemovePlayerShadow)
        }));
    }

    *movement += new MenuEntry(language("Speed Up", "Aller plus vite", "Incromenta velocità"), Helpers::ChooseEntry(Movement::Gen6::SpeedUp, Movement::Gen7::SpeedUp), note + language("only applies to walk and run speeds, and works with D-Pad.", "cela s'applique uniquement aux vitesses de marche et de course, et fonctionne avec la croix directionnelle.", "si applica solamente alla Camminata e alla Corsa e funziona con il D-Pad."));
    *movement += new MenuEntry(language("Bypass Walls", "Passer à travers les murs", "Oltrepassa i muri"), Helpers::ChooseEntry(Movement::Gen6::BypassWalls, Movement::Gen7::BypassWalls));

    if (group == Group::SM || group == Group::USUM)
        *movement += new MenuEntry(language("Time of Day", "Heure du jour", "Ora del giorno"), nullptr, Movement::Gen7::TimeOfDay);

    menu += movement;

    MenuFolder *misc = new MenuFolder(language("Miscellaneous", "Divers", "Varie"));

    if (group == Group::ORAS)
        *misc += new MenuEntry(language("Weather", "Météo", "Meteo"), Misc::Weather, Misc::WeatherKB);

    MenuFolder *pokemon = new MenuFolder("Pokémon");
    *pokemon += new MenuEntry(language("Is Renamable", "Est renommable", "È rinominabile"), Misc::IsRenamable, note + language("you will be able to rename any Pokémon despite it not being at your ownership.", "vous pourrez renommer n'importe quel Pokémon même s'il n'est pas en votre possession.", "potrai rinominare qualsiasi Pokémon anche se non sei il proprietario originale."));
    *pokemon += new MenuEntry(language("Learn Any Teachables", "Apprendre tous les apprenables", "Insegna tutte le mosse"), Misc::LearnAnyTeachables, note + language("you will be able to teach your Pokémon any moves.", "vous pourrez apprendre n'importe quelle attaque à vos Pokémon.", "potrai insegnare qualsiasi mossa ai tuoi Pokémon."));
    *pokemon += new MenuEntry(language("Get Day Care Egg", "Obtenir un oeuf de la Pension", "Ottieni un uovo dalla Pensione Pokémon"), Misc::GetDayCareEgg);
    *pokemon += new MenuEntry(language("Instant Egg Hatch", "Éclosion instantanée d'œuf", "Schiusa istantanea delle uova"), Helpers::ChooseEntry(Misc::Gen6::InstantEggHatch, Misc::Gen7::InstantEggHatch));

    *pokemon += new MenuFolder(language("Other", "Autre", "Altro"), vector<MenuEntry*>({
        EntryWithHotkey(new MenuEntry(language("View Values in Summary", "Voir les valeurs dans le résumé", "Visualizza valori nel riepilogo"), Helpers::ChooseEntry(Misc::Gen6::ViewValuesInSummary, Misc::Gen7::ViewValuesInSummary), note + language("hold one of the following hotkey(s) to view your Individual and Effort Values.", "maintenez l'une des touches de raccourci suivantes pour afficher vos valeurs individuelles et d'effort.", "clicca uno dei tasti di scelta rapida per visualizzare i Valori Individuali o i Punti Base")), {Hotkey(Key::L, ""), Hotkey(Key::R, "")})
    }));

    *misc += pokemon;
    *misc += new MenuEntry(language("Remove Outlines", "Supprimer les contours", "Rimuovi contorni"), Helpers::ChooseEntry(Misc::Gen6::NoOutlines, Misc::Gen7::NoOutlines), note + language("removes outlines in the overworld and in battles.", "supprime les contours dans le monde extérieur et pendant les combats.", "rimuove i contorni nel mondo esterno e nelle battaglie."));
    *misc += new MenuEntry(language("Fast Dialogs", "Dialogues rapides", "Dialoghi veloci"), Misc::FastDialogs, note + language("game dialogs will be sped up.", "les dialogues du jeu seront accélérés.", "le finestre di dialogo del gioco saranno velocizzate."));
    *misc += new MenuEntry(language("Bypass Text Restricts.", "Dépasser les restrictions de texte", "Ignora le restrizioni di testo"), Misc::BypassTextRestricts);

    if ((group == Group::XY || group == Group::ORAS)) {
        *misc += new MenuFolder(language("Custom Game Keyboard", "Clavier personnalisé du jeu", "Tastiera di gioco Personalizzata"), vector<MenuEntry*>({
            new MenuEntry(language("Config", "config", "Configurazione"), nullptr, Misc::CustomKeyboardConfig, note + language("for the in-game keyboard only. This overrides the 'More' section. Make sure to backup your customized keyboards so you won't have to re-enter the values.", "pour le clavier intégré au jeu. Cela remplace la section 'Plus'. Assurez-vous de sauvegarder vos claviers personnalisés afin de ne pas avoir à saisir à nouveau les valeurs.", "solo per la tastiera di gioco. Questo sostituisce la sezione 'Altro'. Assicuratevi di fare un backup delle tastiere personalizzate per evitare di dover reinserire i valori.")),
            EntryWithHotkey(new MenuEntry(language("Keys", "Les touches", "Chiavi"), Misc::CustomKeys, note + language("press the hotkey(s) below to customize the keys. Press Y to clear keyboard. Accepting unicode values only, can be found elsewhere.", "appuyez sur la ou les touches de raccourci ci-dessous pour personnaliser les touches. Appuyez sur Y pour effacer le clavier. Accepte uniquement les valeurs unicode, qui peuvent être trouvées ailleurs.", "premi i tasti di scelta rapida sotto riportati per personalizzare i tasti. Premi 'Y' per cancellare la tastiera. Accetta solo valori unicode, che possono essere trovati altrove.")), {Hotkey(Key::X, "")})
        }));

        *misc += new MenuEntry(language("Patch Colored Text Crashes", "Corriger les plantages liés aux textes en couleur", "Correzione dei Crash causati dal Testo Colorato"), Misc::PatchColorCrash);
    }

    menu += misc;

    menu += new MenuEntry(language("Settings", "Menu des préférences", "Impostazioni"), nullptr, Settings, note + language("resetting your settings will launch you straight back to the home menu, remember to save your game before doing so.", "réinitialiser vos paramètres vous ramènera directement au menu principal, n'oubliez pas de sauvegarder votre jeu avant de le faire.", "Ripristinare le impostazioni ti riporterà nel Menu HOME, ricorda di salvare il tuo gioco prima di procedere."));
}