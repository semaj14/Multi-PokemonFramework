#include <CTRPluginFramework.hpp>

#include "../../Helpers/KeyboardHelpers.hpp"
#include "../../Helpers.hpp"

#include <time.h>

using namespace CTRPluginFramework;

namespace XY
{
	u8 Box, Slot, Amount;
	
	void GetBoxes(MenuEntry *entry)
	{
		Keyboard KB("Box:");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(2);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u8 Input = *static_cast<const u8 *>(In);
			
			if (Input >= 1 && Input <= 31) 
				return (true);
			
			Error = "The value must be between 1-31.";
			return (false);
		});
		
		static u8 SavedValue;
		KB.Open(Box, SavedValue);
		SavedValue = Box;
	}
	
	void GetSlots(MenuEntry *entry)
	{
		Keyboard KB("Slot:");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(2);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u8 Input = *static_cast<const u8 *>(In);
			
			if (Input >= 1 && Input <= 30) 
				return (true);
			
			Error = "The value must be between 1-30.";
			return (false);
		});	
		
		static u8 SavedValue;
		KB.Open(Slot, SavedValue);
		SavedValue = Slot;
	}
	
	void GetAmount(MenuEntry *entry)
	{
		Keyboard KB("Amount:");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(2);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u8 Input = *static_cast<const u8 *>(In);
			
			if (Input + Slot >= 1 && Input + Slot <= 30) 
				return (true);
			
			Error = "The value must be between 1-" + std::to_string(30-Slot) + ".";
			return (false);
		});
		
		static u8 SavedValue;
		KB.Open(Amount, SavedValue);
		SavedValue = Amount;
	}
	
	void Cloning(MenuEntry *entry)
	{
		static u32 Address = 0x8C861C8;
		
		GetBoxes(entry);
		
		if (!Controller::IsKeyPressed(Key::B))
		{
			GetSlots(entry);
			
			if (!Controller::IsKeyPressed(Key::B))
			{
				GetAmount(entry);
				
				if (!Controller::IsKeyPressed(Key::B))
				{
					// Ensures that the chosen box is not 0; chosen slot is not 0; and chosen amount is not 0
					if (Box > 0 && Slot > 0 && Amount > 0)
					{
						// Copies the memory of the start location for x amount of times depending on the amount
						for (int i = 0; i < Amount; i++)
                            Process::CopyMemory((u8*) (i * 0xE8 + (((Slot - 1) * 0xE8) + ((Box - 1) * 0x1B30 + Address)) + 0xE8), (u8*) ((((Slot - 1) * 0xE8) + ((Box - 1) * 0x1B30 + Address))), 0xE8);
						
						MessageBox("The cloning operation has been operated successfully, please refresh your tab to see the cloned Pokemon!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
					}
				}
			}
		}
		
		if (Controller::IsKeyPressed(Key::B))
			MessageBox("The cloning operation has failed due to an interruption, please try again later!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
	}
	
	void Pokemon1(MenuEntry *entry)
	{
		static u32 Address[2] =
		{
			0x8C7FF44,
			0x8C861C8
		};
		
		int& KBValue = *GetArg<int>(entry);
		
		std::vector<std::string> KBOptions =
		{
			"Delete",
			"Take Back"
		};
		
		Keyboard KB(entry->Name() + ":");
		KB.Populate(KBOptions, false);
		KBValue = KB.Open();
		
		if (KBValue == 0) // Route 7 Day Care
		{
			// Checks if there is a Pokemon to delete or not. 0x0 meaning nothing and 0x1 meaning there is a Pokemon
			if (READ32(Address[0], g_Data32) && g_Data32 == 0x0)
				MessageBox("There is no Pokemon to delete!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			
			if (READ32(Address[0], g_Data32) && g_Data32 >= 0x1)
			{
				// Goes through the entire Pokemon's data length and writes 0x0
				for (u8 i = 0x0; i < 0xE4; i++)
					WRITE32(Address[0] + 0x8 + i, 0x0);
				
				WRITE32(Address[0] + 0x4, 0x0);
				WRITE32(Address[0], 0x0);
				MessageBox("Pokemon has been deleted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
		
		if (KBValue == 1) // Route 7 Day Care
		{
			// Checks if there is a Pokemon to take back or not. 0x0 meaning nothing and 0x1 meaning there is a Pokemon
			if (READ32(Address[0], g_Data32) && g_Data32 == 0x0)
				MessageBox("There is no Pokemon to take back!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			
			if (READ32(Address[0], g_Data32) && g_Data32 >= 0x1)
			{
				if (READ32(Address[1], g_Data32) && g_Data32 == 0x0)
				{
					Process::CopyMemory((u8*) (Address[1]), (u8*) (Address[0] + 0x8), 0xE8);
					
					// Goes through the entire Pokemon's data length and writes 0x0 after it has been taken back by a memory copy
					for (u8 i = 0x0; i < 0xE4; i++)
						WRITE32(Address[0] + 0x8 + i, 0x0);
					
					WRITE32(Address[0] + 0x4, 0x0);
					WRITE32(Address[0], 0x0);
					MessageBox("Pokemon has been taken back!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
				}
				
				else if (READ32(Address[1], g_Data32) != 0x0)
					MessageBox("Destination: Box 1 Slot 1 is not empty!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
	}
	
	void Pokemon2(MenuEntry *entry)
	{
		static u32 Address[2] =
		{
			0x8C80034,
			0x8C861C8
		};
		
		int& KBValue = *GetArg<int>(entry);
		
		std::vector<std::string> KBOptions =
		{
			"Delete",
			"Take Back"
		};
		
		Keyboard KB(entry->Name() + ":");
		KB.Populate(KBOptions, false);
		KBValue = KB.Open();
		
		if (KBValue == 0) // Route 7 Day Care
		{
			// Checks if there is a Pokemon to delete or not. 0x0 meaning nothing and 0x1 meaning there is a Pokemon
			if (READ32(Address[0], g_Data32) && g_Data32 == 0x0)
				MessageBox("There is no Pokemon to delete!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			
			if (READ32(Address[0], g_Data32) && g_Data32 >= 0x1)
			{
				// Goes through the entire Pokemon's data length and writes 0x0
				for (u8 i = 0x0; i < 0xE4; i++)
					WRITE32(Address[0] + 0x8 + i, 0x0);
				
				WRITE32(Address[0] + 0x4, 0x0);
				WRITE32(Address[0], 0x0);
				MessageBox("Pokemon has been deleted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
		
		if (KBValue == 1) // Route 7 Day Care
		{
			// Checks if there is a Pokemon to take back or not. 0x0 meaning nothing and 0x1 meaning there is a Pokemon
			if (READ32(Address[0], g_Data32) && g_Data32 == 0x0)
				MessageBox("There is no Pokemon to take back!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			
			if (READ32(Address[0], g_Data32) && g_Data32 >= 0x1)
			{
				if (READ32(Address[1], g_Data32) && g_Data32 == 0x0)
				{
					Process::CopyMemory((u8*) (Address[1]), (u8*) (Address[0] + 0x8), 0xE8);
					
					// Goes through the entire Pokemon's data length and writes 0x0 after it has been taken back by a memory copy
					for (u8 i = 0x0; i < 0xE4; i++)
						WRITE32(Address[0] + 0x8 + i, 0x0);
					
					WRITE32(Address[0] + 0x4, 0x0);
					WRITE32(Address[0], 0x0);
					MessageBox("Pokemon has been taken back!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
				}
				
				else if (READ32(Address[1], g_Data32) != 0x0)
					MessageBox("Destination: Box 1 Slot 1 is not empty!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
	}
	
	void InstantEgg(MenuEntry *entry)
	{
		static u32 Address = 0x8C67234;
		
		if (READ16(Address, g_Data16) && g_Data16 != 0x100)
			WRITE16(Address, 0x100);
	}
	
	void InstantEggHatch(MenuEntry *entry)
	{
		static u32 Address = 0x8C68261;
		
		if (READ16(Address, g_Data16) && g_Data16 != 0x101)
			WRITE16(Address, 0x101);
	}
	
	void QuickFriendshipGain(MenuEntry *entry)
	{
		static u32 Address = 0x8C68264;
		
		WRITE16(Address, 0x7F);
	}
	
	void ComputerAnywhere(MenuEntry *entry)
	{
		static u32 Address = 0x3BBFA8;
		
		if (entry->IsActivated())
			WRITE32(Address, 0xE3A00004);
		
		if (!entry->IsActivated())
			WRITE32(Address, 0xE3A00018);
	}
	
	void ExportAndImportBin(MenuEntry *entry)
	{
		static u32 Address = 0x8C861C8;
		
		int FileIndex;
		std::vector<std::string> ListOfFiles;
		std::vector<std::string> ListOfFileNames;
		std::string Extension = ".bin";
		int ListOfIndex;
		
		Directory CheckFiles(Bin);
		CheckFiles.ListFiles(ListOfFiles, Extension);
		ListOfFileNames = ListOfFiles;
		ListOfIndex = ListOfFileNames.size();
		
		// Prevents backup overdose by if the list of index is greator than or equal to 20
		if (ListOfIndex >= 20)
		{
			if (MessageBox("Maximum backup limit reached! Would you like to erase all backups?", DialogType::DialogYesNo).SetClear(ClearScreen::Both)())
			{
				for (int i = 0; i < ListOfIndex; i++)
					File::Remove(Bin + ListOfFileNames[i]);
				
				MessageBox("All backups have been erased.", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
		
		time_t RawTime;
		struct tm * TimeInfo;
		char TimeStamp[80];
		
		time(&RawTime);
		TimeInfo = localtime(&RawTime);
		strftime(TimeStamp, 80, "[%F_%I-%M-%S]", TimeInfo);
		std::string FileName = TimeStamp + Extension;
		
		int KBValue;
		
		std::vector<std::string> KBOptions =
		{
			"Export",
			"Import"
		};
		
		Keyboard KB(entry->Name() + ":");
		KB.Populate(KBOptions, false);
		
		if (ListOfIndex <= 20)
			KBValue = KB.Open();
		
		if (KBValue == 0) // Export
		{
			// Checks if the Bin directory already exists or not, otherwise create one
			if (!Directory::IsExists(Bin))
				Directory::Create(Bin);
			
			if (ListOfIndex <= 20)
			{
				File DumpBox(Bin + FileName, File::RWC);
				DumpBox.Dump(Address, 0x34AD0);
				MessageBox("The Box exportation operation has been operated successfully, to see the exported files, choose the 2nd option!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
		
		if (KBValue == 1) // Import
		{
			// Ensure that the user has at least 1 backup file
			if (ListOfIndex == 0)
				MessageBox("You have 0 backup(s) to recover from!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			
			if (ListOfIndex >= 1)
			{
				KB.Populate(ListOfFileNames);
				FileIndex = KB.Open();
				
				if (!Controller::IsKeyPressed(Key::B))
				{
					File InjectBox(Bin + ListOfFileNames[FileIndex]);
					InjectBox.Inject(Address, 0x34AD0);
					MessageBox("The Box importation operation has been operated successfully, please refresh your tab to see the injected Boxes!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
				}
			}
		}
	}
	
	void ExportAndImportPk6(MenuEntry *entry)
	{
		static u32 Address = 0x8C861C8;
		
		int FileIndex;
		std::vector<std::string> ListOfFiles;
		std::vector<std::string> ListOfFileNames;
		std::string Extension = ".Pk6";
		int ListOfIndex;
		
		Directory CheckFiles(Pk6);
		CheckFiles.ListFiles(ListOfFiles, Extension);
		ListOfFileNames = ListOfFiles;
		ListOfIndex = ListOfFileNames.size();
		
		// Prevents backup overdose by if the list of index is greator than or equal to 20
		if (ListOfIndex >= 20)
		{
			if (MessageBox("Maximum backup limit reached! Would you like to erase all backups?", DialogType::DialogYesNo).SetClear(ClearScreen::Both)())
			{
				for (int i = 0; i < ListOfIndex; i++)
					File::Remove(Pk6 + ListOfFileNames[i]);
				
				MessageBox("All backups have been erased.", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
		
		time_t RawTime;
		struct tm * TimeInfo;
		char TimeStamp[80];
		
		time(&RawTime);
		TimeInfo = localtime(&RawTime);
		strftime(TimeStamp, 80, "[%F_%I-%M-%S]", TimeInfo);
		std::string FileName = TimeStamp + Extension;
		
		int& KBValue = *GetArg<int>(entry);
		
		std::vector<std::string> KBOptions =
		{
			"Export",
			"Import"
		};
		
		Keyboard KB(entry->Name() + ":");
		KB.Populate(KBOptions, false);
		
		if (ListOfIndex <= 20)
			KBValue = KB.Open();
		
		if (KBValue == 0) // Export
		{
			// Checks if the Pk6 directory already exists or not, otherwise create one
			if (!Directory::IsExists(Pk6))
				Directory::Create(Pk6);
			
			if (ListOfIndex <= 20)
			{
				GetBoxes(entry);
				
				if (!Controller::IsKeyPressed(Key::B))
				{
					GetSlots(entry);
					
					if (!Controller::IsKeyPressed(Key::B))
					{
						if (Box >= 1 && Slot >= 1)
						{
							File DumpPk6(Pk6 + FileName, File::RWC);
							DumpPk6.Dump((((Slot - 1) * 0xE8) + ((Box - 1) * 0x1B30 + Address)), 0xE8);
							MessageBox("The Pokemon exportation operation has been operated successfully, to see the exported files, choose the 2nd option!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
						}
					}
				}
				
				if (Controller::IsKeyPressed(Key::B))
					MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
		
		if (KBValue == 1) // Import
		{
			// Ensure that the user has at least 1 backup file
			if (ListOfIndex == 0)
				MessageBox("You currently have 0 backup(s) to recover from!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			
			if (ListOfIndex >= 1)
			{
				GetBoxes(entry);
				
				if (!Controller::IsKeyPressed(Key::B))
				{
					GetSlots(entry);
					
					if (!Controller::IsKeyPressed(Key::B))
					{
						// Populate the keyboard with the list of file names
						KB.Populate(ListOfFileNames);
						FileIndex = KB.Open();
						
						if (!Controller::IsKeyPressed(Key::B))
						{
							if (Box >= 1 && Slot >= 1)
							{
								File InjectPk6(Pk6 + ListOfFileNames[FileIndex]);
								InjectPk6.Inject((((Slot - 1) * 0xE8) + ((Box - 1) * 0x1B30 + Address)), 0xE8);
								MessageBox("The Pokemon importation operation has been operated successfully, please refresh your tab to see the injected files!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
							}
						}
					}
				}
				
				if (Controller::IsKeyPressed(Key::B))
					MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
	}
	
	void StealPokemonInTrade(MenuEntry *entry)
	{
		static u32 Address[3] =
		{
			0x850CC94,
			0x850CCC4,
			0x8C861C8
		};
		
		// Checks if the address' data is 0x5544 or not, if it is, then the user is not trade
		if (READ32(Address[0], g_Data32) && g_Data32 == 0x5544)
		{
			if (entry->Hotkeys[0].IsDown()) // Must have the user hold down the hotkey
			{
				// Reads if the Pokemon data is empty or not, otherwise steal
				if (READ32(Address[1], g_Data32) && g_Data32 != 0x0)
					Process::CopyMemory((u8*) (Address[3]), (u8*) (Address[1]), 0xE8);
			}
		}
	}
	
	void UnlockAllBoxes(MenuEntry *entry)
	{
		static u32 Address = 0x8C6AC26;
		
		// Checks if the user already has 31 boxes unlocked
		if (READ8(Address, g_Data8) && g_Data8 < 0x1F)
		{
			WRITE8(Address, 0x1F);
			MessageBox("You have finally unlocked all the Boxes available in your Personal Computer!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		}
		
		else MessageBox("You have already unlocked all the Boxes available in your Personal Computer!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
	}
}