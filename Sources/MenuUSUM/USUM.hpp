#include <CTRPluginFramework.hpp>

#include "Includes/USUM1.hpp"
#include "Includes/USUM2.hpp"
#include "Includes/USUM3.hpp"
#include "Includes/USUM4.hpp"
#include "Includes/USUM5.hpp"

#include "../Helpers.hpp"
#include "../Helpers/PK7.hpp"
#include "../Helpers/HotkeyHelpers.hpp"

using namespace CTRPluginFramework;

namespace USUM
{
	void Menu(PluginMenu &Menu)
	{
		// Battle cheats
		MenuFolder *Battle = new MenuFolder("Battle");
		MenuFolder *Primary = new MenuFolder("Primary");
		MenuFolder *Stats = new MenuFolder("Stats");
		*Stats += new MenuEntry("Attack", SetAttackStat, GetAttackStat);
		*Stats += new MenuEntry("Defense", SetDefenseStat, GetDefenseStat);
		*Stats += new MenuEntry("Special Atk", SetSpAtkStat, GetSpAtkStat);
		*Stats += new MenuEntry("Special Def", SetSpDefStat, GetSpDefStat);
		*Stats += new MenuEntry("Speed", SetSpeedStat, GetSpeedStat);
		*Primary += Stats;
		MenuFolder *Boosts = new MenuFolder("Boosts");
		*Boosts += new MenuEntry("Attack", SetAttackBoost, GetAttackBoost);
		*Boosts += new MenuEntry("Defense", SetDefenseBoost, GetDefenseBoost);
		*Boosts += new MenuEntry("Special Atk", SetSpAtkBoost, GetSpAtkBoost);
		*Boosts += new MenuEntry("Special Def", SetSpDefBoost, GetSpDefBoost);
		*Boosts += new MenuEntry("Speed", SetSpeedBoost, GetSpeedBoost);
		*Boosts += new MenuEntry("Accuracy", SetAccuracyBoost, GetAccuracyBoost);
		*Boosts += new MenuEntry("Evasiveness", SetEvasivenessBoost, GetEvasivenessBoost);
		*Primary += Boosts;
		*Primary += new MenuEntry("Type 1", SetType1, GetType1);
		*Primary += new MenuEntry("Type 2", SetType2, GetType2);
		*Primary += new MenuEntry("Ability", SetAbility, GetAbility);
		*Primary += EntryWithHotkey(new MenuEntry("Condition", SetCondition, GetCondition, "To apply or remove any condition on your current Pokémon, press on the following hotkeys."), {Hotkey(Key::L, "\nApply"), Hotkey(Key::R, "Remove")});
		*Primary += new MenuEntry("Unlimited HP", UnlimitedHP);
		*Primary += new MenuEntry("Unlimited AP", UnlimitedAP);
		*Primary += new MenuEntry("Item Held", SetItemHeld, GetItemHeld);
		*Primary += new MenuEntry("Interrupt Charge", InterruptCharge);
		*Primary += new MenuEntry("Interrupt Recharge", InterruptRecharge);
		*Primary += new MenuEntry("One Hit K-O", OneHitKO);
		*Battle += Primary;
		*Battle += new MenuEntry("Experience", SetExperience, GetExperience, "Lets you multiply the amount of experience you gain after defeating an enemy.");
		MenuFolder *Additionals = new MenuFolder("Additionals");
		*Additionals += EntryWithHotkey(new MenuEntry("Access Bag", AccessBag, "You must press on 'FIGHT' whilst holding the following hotkeys."), {Hotkey(Key::Start, "\nAccess Bag")});
		*Additionals += new MenuEntry("100% Shiny", OneHundredPercentShiny);
		*Additionals += new MenuEntry("100% Catch", OneHundredPercentCatch);
		*Additionals += new MenuEntry("Trainer Rematch", TrainerRematch);
		*Additionals += EntryWithHotkey(new MenuEntry("Z-Moves Without Crystal", ZMovesWithoutCrystal, "If you would like to use Z-Moves without their crystals, then hold the following hotkeys."), {Hotkey(Key::R, "\nZ-Move Without Crystal")});
		*Additionals += EntryWithHotkey(new MenuEntry("Mega Evolve Without Stone", MegaEvolveWithoutStone, "Be aware that most Pokemon only have 1 Mega Evolution form! You must press the following hotkeys for the other form."), {Hotkey(Key::L, "\nOther Form")});
		*Battle += Additionals;
		*Battle += new MenuEntry("Pokemon Spawner", SetPokemonSpawner, GetPokemonSpawner);
		*Battle += new MenuEntry("Catch Trainer Pokemon", CatchTrainerPokemon);
		Menu += Battle;
		
		// Computer cheats
		MenuFolder *Computer = new MenuFolder("Computer");
		*Computer += new MenuEntry("Cloning", nullptr, Cloning);
		MenuFolder *DayCare = new MenuFolder("Nursery");
		*DayCare += new MenuEntry("Pokémon 1", nullptr, Pokemon1);
		*DayCare += new MenuEntry("Pokémon 2", nullptr, Pokemon2);
		*DayCare += new MenuEntry("Instant Egg", InstantEgg);
		*DayCare += new MenuEntry("Instant Egg Hatch", InstantEggHatch);
		*DayCare += new MenuEntry("Quick Friendship Gain", QuickFriendshipGain);
		*Computer += DayCare;
		*Computer += new MenuEntry("Computer Anywhere", ComputerAnywhere, "You must click on the 'Options' icon on the pause menu if you would like to access your Personal Computer.");
		*Computer += new MenuEntry("Export & Import .bin", nullptr, ExportAndImportBin);
		*Computer += new MenuEntry("Export & Import .pk7", nullptr, ExportAndImportPk7);
		*Computer += EntryWithHotkey(new MenuEntry("Steal Pokémon in Trade", StealPokemonInTrade, "This will overwrite any Pokémon sitting in Slot 1 of Box 1. If you understand, you may press on the following hotkeys."), {Hotkey(Key::Start, "\nSteal Pokémon")});
		*Computer += new MenuEntry("Unlock All Boxes", nullptr, UnlockAllBoxes);
		Menu += Computer;
		
		// Information cheats
		MenuFolder *Information = new MenuFolder("Information");
		MenuFolder *Inventory = new MenuFolder("Inventory");
		MenuFolder *BagItems = new MenuFolder("Items");
		*BagItems += new MenuEntry("Category 1", nullptr, Category1);
		*BagItems += new MenuEntry("Category 2", nullptr, Category2);
		*BagItems += new MenuEntry("Category 3", nullptr, Category3);
		*BagItems += new MenuEntry("Category 4", nullptr, Category4);
		*BagItems += new MenuEntry("Category 5", nullptr, Category5);
		*BagItems += new MenuEntry("Category 6", nullptr, Category6);
		*Inventory += BagItems;
		*Inventory += new MenuEntry("Money", SetMoney, GetMoney);
		*Inventory += new MenuEntry("Battle Points", SetBattlePoints, GetBattlePoints);
		*Inventory += new MenuEntry("Festival Coins", SetFestivalCoins, GetFestivalCoins);
		*Information += Inventory;
		*Information += EntryWithHotkey(new MenuEntry("Pokédex", SetPokedex, GetPokedex, "If you would like to unlock the other Pokédex elements, you may press on the following hotkeys."), {Hotkey(Key::Start, "\nUnlocker")});
		*Information += new MenuEntry("Nickname", nullptr, Nickname);
		*Information += new MenuEntry("Playtime", SetPlaytime, GetPlaytime);
		*Information += new MenuEntry("Identity 1", nullptr, Identity1);
		*Information += new MenuEntry("Identity 2", nullptr, Identity2);
		*Information += new MenuEntry("Language", SetLanguage, GetLanguage, "You must save and reload the game while having this cheat enabled.");
		*Information += new MenuEntry("Time of Day", nullptr, TimeOfDay);
		Menu += Information;
		
		// Miscellaneous cheats
		MenuFolder *Miscellaneous = new MenuFolder("Miscellaneous");
		MenuFolder *Movement = new MenuFolder("Movement");
		*Movement += new MenuEntry("Moon Walk", MoonWalk);
		*Movement += new MenuEntry("Walk & Run Speed", SetWalkAndRunSpeed, GetWalkAndRunSpeed);
		*Movement += EntryWithHotkey(new MenuEntry("Walk Through Walls", WalkThroughWalls, "Hold the following hotkeys if you would like to walk through walls."), {Hotkey(Key::R, "\nWalk Through Walls")});
		*Movement += new MenuEntry("Repel Lasts Forever", RepelLastsForever);
		*Movement += EntryWithHotkey(new MenuEntry("Camera Zoom-Out", CameraZoomOut, "You may need to refresh the screen through the 'Options' icon on the pause menu before pressing a hotkey."), {Hotkey(Key::L, "\nZoom-Out"), Hotkey(Key::R, "Zoom-In")});
		*Miscellaneous += Movement;
		*Miscellaneous += new MenuEntry("Instant Dialogs", InstantDialogs);
		*Miscellaneous += new MenuEntry("No Outlines", NoOutlines);
		*Miscellaneous += new MenuEntry("No Player Shadow", NoPlayerShadow);
		MenuFolder *QuickResponse = new MenuFolder("Quick Response");
		*QuickResponse += new MenuEntry("QR 100 Points", QR100Points);
		*QuickResponse += new MenuEntry("No QR Wait Time", NoQRWaitTime);
		*Miscellaneous += QuickResponse;
		Menu += Miscellaneous;
		
		// Appearance cheats
		MenuFolder *Appearance = new MenuFolder("Appearance");
		*Appearance += new MenuEntry("Change Gender", nullptr, ChangeGender);
		*Appearance += new MenuEntry("Change Skin Tone", nullptr, ChangeSkinTone, "In order for the new skin tone to be applied, you must save and reload the game!");
		*Appearance += new MenuEntry("Receive All Clothes", ReceiveAllClothes);
		Menu += Appearance;
		
		Menu += new MenuEntry("Disable NFC", DisableNFC);
	}
}