#include <CTRPluginFramework.hpp>

#include "Includes/XY1.hpp"
#include "Includes/XY2.hpp"
#include "Includes/XY3.hpp"
#include "Includes/XY4.hpp"

#include "../Helpers.hpp"
#include "../Helpers/PK6.hpp"
#include "../Helpers/HotkeyHelpers.hpp"

using namespace CTRPluginFramework;

namespace XY
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
		*Additionals += new MenuEntry("Infinite Mega Evolutions", InfiniteMegaEvolutions, "You may Mega Evolve more than once, but only if the Pokémon is eligible and is holding a stone corresponding to their species.");
		*Battle += Additionals;
		*Battle += new MenuEntry("Legendary Rematch", SetLegendaryRematch, GetLegendaryRematch);
		*Battle += new MenuEntry("Unlock Mega Evolution", nullptr, UnlockMegaEvolution);
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
		*Computer += new MenuEntry("Computer Anywhere", ComputerAnywhere, "You must click on the 'Options' icon on the bottom screen if you would like to access your Personal Computer.");
		*Computer += new MenuEntry("Export & Import .bin", nullptr, ExportAndImportBin);
		*Computer += new MenuEntry("Export & Import .pk6", nullptr, ExportAndImportPk6);
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
		*Inventory += BagItems;
		*Inventory += new MenuEntry("Miles", SetMiles, GetMiles);
		*Inventory += new MenuEntry("Money", SetMoney, GetMoney);
		*Inventory += new MenuEntry("Battle Points", SetBattlePoints, GetBattlePoints);
		*Information += Inventory;
		*Information += EntryWithHotkey(new MenuEntry("Pokédex", SetPokedex, GetPokedex, "If you would like to unlock the other Pokédex elements, you may press on the following hotkeys."), {Hotkey(Key::Start, "\nUnlocker")});
		*Information += new MenuEntry("Nickname", nullptr, Nickname);
		*Information += new MenuEntry("Playtime", SetPlaytime, GetPlaytime);
		*Information += new MenuEntry("Identity 1", nullptr, Identity1);
		*Information += new MenuEntry("Identity 2", nullptr, Identity2);
		*Information += new MenuEntry("Language", SetLanguage, GetLanguage, "You must save and reload the game while having this cheat enabled.");
		*Information += new MenuEntry("Gym Badges", nullptr, GymBadges);
		Menu += Information;
		
		// Miscellaneous cheats
		MenuFolder *Miscellaneous = new MenuFolder("Miscellaneous");
		MenuFolder *Movement = new MenuFolder("Movement");
		*Movement += EntryWithHotkey(new MenuEntry("Warper", SetWarper, GetWarper, "To warp to a new location you must hold the following hotkeys."), {Hotkey(Key::R, "\nWarper")});
		*Movement += new MenuEntry(Color::Orange << "Walk Through Walls", WalkThroughWalls, "You are required to reload the screen through accessing a pause menu element or an icon on the bottom screen.");
		*Movement += new MenuEntry("Fly Anywhere", FlyAnywhere, "Press the Pokemon's 'SUMMARY' button if you would like to use Fly anywhere regardless of its restrictions!");
		*Movement += new MenuEntry("Repel Lasts Forever", RepelLastsForever);
		*Miscellaneous += Movement;
		*Miscellaneous += EntryWithHotkey(new MenuEntry("O-Power", SetOPower, GetOPower, "To unlock all the other O-Powers, press the follwing hotkeys."), {Hotkey(Key::Start, "\nUnlocker")});
		*Miscellaneous += new MenuEntry("No Outlines", NoOutlines);
		*Miscellaneous += new MenuEntry("Instant Dialogs", InstantDialogs, "Text dialogs will be loaded at instant speed.");
		Menu += Miscellaneous;
	}
}