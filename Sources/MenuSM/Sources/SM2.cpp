#include <CTRPluginFramework.hpp>
#include <time.h>
#include "../../Helpers/Includes/Helpers.hpp"

using namespace CTRPluginFramework;

namespace SM
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
			
			if (Input >= 1 && Input <= 32) 
				return (true);
			
			Error = "The value must be between 1-32.";
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
		static u32 Address = 0x330D9838;
		
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
			0x3313EC00,
			0x330D9838
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
		
		if (KBValue <= -1)
		{
			MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			return;
		}
		
		if (KBValue == 0) // Paniola Ranch Day Care
		{
			// Checks if there is a Pokemon to delete or not. 0x0 meaning nothing and 0x1 meaning there is a Pokemon
			if (READ8(Address[0], g_Data8) && g_Data8 == 0x0)
				MessageBox("There is no Pokemon to delete!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			
			if (READ8(Address[0], g_Data8) && g_Data8 >= 0x1)
			{
				// Goes through the entire Pokemon's data length and writes 0x0
				for (u8 i = 0x0; i < 0xE4; i++)
					WRITE32(Address[0] + 0x1 + i, 0x0);
				
				WRITE8(Address[0], 0x0);
				MessageBox("Pokemon has been deleted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
		
		if (KBValue == 1) // Paniola Ranch Day Care
		{
			// Checks if there is a Pokemon to take back or not. 0x0 meaning nothing and 0x1 meaning there is a Pokemon
			if (READ8(Address[0], g_Data8) && g_Data8 == 0x0)
				MessageBox("There is no Pokemon to take back!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			
			if (READ8(Address[0], g_Data8) && g_Data8 >= 0x1)
			{
				if (READ32(Address[1], g_Data32) && g_Data32 == 0x0)
				{
					Process::CopyMemory((u8*) (Address[1]), (u8*) (Address[0] + 0x1), 0xE8);
					
					// Goes through the entire Pokemon's data length and writes 0x0 after it has been taken back by a memory copy
					for (u8 i = 0x0; i < 0xE4; i++)
						WRITE32(Address[0] + 0x1 + i, 0x0);
					
					WRITE8(Address[0], 0x0);
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
			0x3313ECE9,
			0x330D9838
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
		
		if (KBValue <= -1)
		{
			MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			return;
		}
		
		if (KBValue == 0) // Paniola Ranch Day Care
		{
			// Checks if there is a Pokemon to delete or not. 0x0 meaning nothing and 0x1 meaning there is a Pokemon
			if (READ8(Address[0], g_Data8) && g_Data8 == 0x0)
				MessageBox("There is no Pokemon to delete!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			
			if (READ8(Address[0], g_Data8) && g_Data8 >= 0x1)
			{
				// Goes through the entire Pokemon's data length and writes 0x0
				for (u8 i = 0x0; i < 0xE4; i++)
					WRITE32(Address[0] + 0x1 + i, 0x0);
				
				WRITE8(Address[0], 0x0);
				MessageBox("Pokemon has been deleted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
		
		if (KBValue == 1) // Paniola Ranch Day Care
		{
			// Checks if there is a Pokemon to take back or not. 0x0 meaning nothing and 0x1 meaning there is a Pokemon
			if (READ8(Address[0], g_Data8) && g_Data8 == 0x0)
				MessageBox("There is no Pokemon to take back!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			
			if (READ8(Address[0], g_Data8) && g_Data8 >= 0x1)
			{
				if (READ32(Address[1], g_Data32) && g_Data32 == 0x0)
				{
					Process::CopyMemory((u8*) (Address[1]), (u8*) (Address[0] + 0x1), 0xE8);
					
					// Goes through the entire Pokemon's data length and writes 0x0 after it has been taken back by a memory copy
					for (u8 i = 0x0; i < 0xE4; i++)
						WRITE32(Address[0] + 0x1 + i, 0x0);
					
					WRITE8(Address[0], 0x0);
					MessageBox("Pokemon has been taken back!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
				}
				
				else if (READ32(Address[1], g_Data32) != 0x0)
					MessageBox("Destination: Box 1 Slot 1 is not empty!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
	}
	
    void InstantEgg(MenuEntry *entry)
    {
		static u32 Address = 0x4466A8;
		
		static u32 Data[3] = 
		{
			0xE3A01001, 0xE5C011E0, 0xEA00684B
		};
		
		static u32 Original[3] =
		{
			0x00000000, 0x00000000, 0x00000000
		};
		
		static Clock Timer;
		static bool Waiting = false;
		
		if (entry->Hotkeys[0].IsDown() && !Waiting)
		{
			if (!Process::Patch(Address, Data, 0xC, Original))
				goto Error;
			
			Timer.Restart();
			Waiting = true;
		} 
		
		else if (Timer.HasTimePassed(Seconds(2)) && Waiting)
		{
			if (!Process::Patch(Address, Original, 0xC))
				goto Error;
			
			Waiting = false;
		}
		
		Error: return;
    }
	
    void InstantEggHatch(MenuEntry *entry)
    {
		// Original non-ASM address is 0x330D67A4
		static u32 Address[2] = 
		{
			0x5977C0,
			0x493668
		};
		
		static u32 Data[7] = 
		{
			0xE59D000C, 0xE59F500C, 0xE1500005, 0x03A00000,
			0x11A00004, 0xE12FFF1E, 0x006D08C0
		};
		
		static u32 Jump[1] =
		{
			0xEB041054
		};
		
		static u32 Original[1] =
		{
			0x00000000
		};
		
		if (entry->WasJustActivated())
		{
			if (!Process::Patch(Address[0], Data, 0x1C))
				goto Error;
			
			if (!Process::Patch(Address[1], Jump, 0x4, Original))
				goto Error;
		} 
		
		else if (!entry->IsActivated())
		{
			if (!Process::Patch(Address[1], Original, 0x4))
				goto Error;
		}
		
		Error: return;
    }
	
	void QuickFriendshipGain(MenuEntry *entry)
	{
		static u32 Address = 0x330D67AA;
		
		WRITE16(Address, 0xFF);
	}
	
	void ComputerAnywhere(MenuEntry *entry)
	{
		static u32 Address[4] =
		{
			0x597878,
			0x37E5E4,
			0x374C3C,
			0x5978A8,
		};
		
		static u32 Buffer[34] =
		{
			0xE92D400E, 0xE59F1074, 0xE5912000, 0xE3A03000, 
			0xE5813000, 0xE3A03C13, 0xE2833093, 0xE1520003, 
			0x03A04000, 0x11A04000, 0xE8BD800E, 0xE350000E, 
			0xEAF77958, 0xE92D400F, 0xE24DD010, 0xE3A00000, 
			0xE58D0000, 0xE58D0004, 0xE58D0008, 0xE58D000C, 
			0xE1A03000, 0xE1A02000, 0xE3A01C13, 0xE2811093, 
			0xE59F0018, 0xE5801000, 0xE59F0014, 0xE5900000, 
			0xEBF7D6DC, 0xE3A00002, 0xE28DD010, 0xE8BD800F, 
			0x00638000, 0x006740BC,  
		};
		
		if (entry->WasJustActivated()) 
		{
			if (!Process::Patch(Address[0], Buffer, 0x88))
				goto Error;
			
			if (!WRITE32(Address[1], 0xEB0864A3))
				goto Error;
			
			if (!WRITE32(Address[2], 0xEB088B18))
				goto Error;
			
			if (!WRITE32(Address[3], 0x1AF77958))
				goto Error;
		}
		
		else if (!entry->IsActivated())
		{
			if (!WRITE32(Address[3], 0xEAF70DE3))
				goto Error;
		}
		
		Error: return;
	}
	
	void ExportAndImportBin(MenuEntry *entry)
	{
		static u32 Address = 0x330D9838;
		
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
				DumpBox.Dump(Address, 0x365FC);
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
					InjectBox.Inject(Address, 0x365FC);
					MessageBox("The Box importation operation has been operated successfully, please refresh your tab to see the injected Boxes!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
				}
			}
		}
	}
	
	void ExportAndImportPk7(MenuEntry *entry)
	{
		static u32 Address = 0x330D9838;
		
		int FileIndex;
		std::vector<std::string> ListOfFiles;
		std::vector<std::string> ListOfFileNames;
		std::string Extension = ".Pk7";
		int ListOfIndex;
		
		Directory CheckFiles(Pk7);
		CheckFiles.ListFiles(ListOfFiles, Extension);
		ListOfFileNames = ListOfFiles;
		ListOfIndex = ListOfFileNames.size();
		
		// Prevents backup overdose by if the list of index is greator than or equal to 20
		if (ListOfIndex >= 20)
		{
			if (MessageBox("Maximum backup limit reached! Would you like to erase all backups?", DialogType::DialogYesNo).SetClear(ClearScreen::Both)())
			{
				for (int i = 0; i < ListOfIndex; i++)
					File::Remove(Pk7 + ListOfFileNames[i]);
				
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
			// Checks if the Pk7 directory already exists or not, otherwise create one
			if (!Directory::IsExists(Pk7))
				Directory::Create(Pk7);
			
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
							File DumpPk7(Pk7 + FileName, File::RWC);
							DumpPk7.Dump((((Slot - 1) * 0xE8) + ((Box - 1) * 0x1B30 + Address)), 0xE8);
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
								File InjectPk7(Pk7 + ListOfFileNames[FileIndex]);
								InjectPk7.Inject((((Slot - 1) * 0xE8) + ((Box - 1) * 0x1B30 + Address)), 0xE8);
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
			0x32A87098,
			0x32A870C8,
			0x330D9838
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
		static u32 Address = 0x330D982D;
		
		// Checks if the user already has 32 boxes unlocked
		if (READ8(Address, g_Data8) && g_Data8 < 0x20)
		{
			WRITE8(Address, 0x20);
			MessageBox("You have finally unlocked all the Boxes available in your Personal Computer!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		}
		
		else MessageBox("You have already unlocked all the Boxes available in your Personal Computer!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
	}
}