#include <CTRPluginFramework.hpp>
#include <time.h>
#include "../../Helpers/Includes/Helpers.hpp"

using namespace CTRPluginFramework;

namespace USUM
{
	static u32 Playtime; static u16 Value1; static u8 Value2, Value3;
	
	#define SizeOfCategory1 sizeof(Category1IDs) / sizeof(Category1IDs[0])
	#define SizeOfCategory2 sizeof(Category2IDs) / sizeof(Category2IDs[0])
	#define SizeOfCategory3 sizeof(Category3IDs) / sizeof(Category3IDs[0])
	#define SizeOfCategory4 sizeof(Category4IDs) / sizeof(Category4IDs[0])
	#define SizeOfCategory5 sizeof(Category5IDs) / sizeof(Category5IDs[0])
	#define SizeOfCategory6 sizeof(Category6IDs) / sizeof(Category6IDs[0])
	
	#define SizeOfUnreleased sizeof(UnreleasedIDs) / sizeof(UnreleasedIDs[0])
	
	// All the Medicine IDs
	static int Category1IDs[] =
	{
		17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
		42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 65, 66, 67,
		
		134, 504, 565, 566, 567, 568, 569, 570, 591, 645, 708, 709, 852
	};
	
	// All the Item IDs
	static int Category2IDs[] =
	{
		68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 
		93, 94, 99, 
		
		100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 116, 117, 118, 119, 135, 136, 137,
		213, 214, 215, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233,
		234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253,
		254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273,
		274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293,
		294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313,
		314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 499, 534, 535, 537, 538, 539,
		540, 541, 542, 543, 544, 545, 546, 547, 548, 549, 550, 551, 552, 553, 554, 555, 556, 557, 558, 559,
		560, 561, 562, 563, 564, 571, 572, 573, 580, 581, 582, 583, 584, 585, 586, 587, 588, 589, 590, 639,
		640, 644, 646, 647, 648, 649, 650, 656, 657, 658, 659, 660, 661, 662, 663, 664, 665, 666, 667, 668,
		669, 670, 671, 672, 673, 674, 675, 676, 677, 678, 679, 680, 681, 682, 683, 684, 685, 699, 704, 710,
		711, 715, 752, 753, 754, 755, 756, 757, 758, 759, 760, 761, 762, 763, 764, 767, 768, 769, 770, 795,
		796, 844, 849, 853, 854, 855, 856, 879, 880, 881, 882, 883, 884, 904, 905, 906, 907, 908, 909, 910,
		911, 912, 913, 914, 915, 916, 917, 918, 919, 920,
		
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 
		
		492, 493, 494, 495, 496, 497, 498, 576, 851,
		
		55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 
		
		577, 846
    };
	
	// All the TM & HM IDs
	static int Category3IDs[] =
	{
		328, 329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347,
		348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367,
		368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383, 384, 385, 386, 387,
		388, 389, 390, 391, 392, 393, 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407,
		408, 409, 410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 618, 619, 620, 690, 691, 692, 693, 694
	};
	
	// All the Berry IDs
	static int Category4IDs[] =
	{
		149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168,
		169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188,
		189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208,
		209, 210, 211, 212, 686, 687, 688
	};
	
	// All the Key Item IDs
	static int Category5IDs[] =
	{
		216, 465, 466, 628, 629, 631, 632, 638, 705, 706, 765, 773, 797, 841, 842, 843, 845, 847, 850, 857,
		858, 860
	};
	
	// All the Z-Crystal IDs
	static int Category6IDs[] =
	{
		807, 808, 809, 810, 811, 812, 813, 814, 815, 816, 817, 818, 819, 820, 821, 822, 823, 824, 825, 826,
		827, 828, 829, 830, 831, 832, 833, 834, 835, 927, 928, 929, 930, 931, 932
	};
	
	// All the flags for a seen Pokedex. Took forever lol...
	static const u32 Seen[] =
	{
		0x0000007F, 0x8FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF7FAFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFCDFFF, 0xFFFFFFFF,
		0xFDFFFFFF, 0xFFFFFFFF, 0xF7FFFFFF, 0x6FFFFFFF, 0xFF7FFFFF,
		0xDFFFFFFF, 0xFFFFFF7F, 0xFFFFFFFF, 0xFFFFFFE7, 0xFFFFFFFF,
		0xFFCFFFFF, 0x8FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF8DFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFF7FF, 0xFFFFFFFF, 0xFFFCFFBF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFDFF0007, 0xFFEFFFFF,
		0x0FFFFFFF, 0x7FFFFFFF, 0xFFFFFFFC, 0xFFFCFFFF, 0x7E7FF9E7,
		0xFF9C7EF7, 0xFFFFFFFF, 0xFFFFFEFF, 0xF8E3E6FF, 0xFFFFFFFF,
		0xFEFFFFF7, 0xFF3CFFFF, 0x081FFFFF, 0xDFFFFFFC, 0xFFE7FFFF,
		0x39FFDFFF, 0xFFFFC090, 0xF9FFFFFF, 0xFFFFFFFF, 0xFE3FFFFF,
		0x1FF39FBF, 0xFFFFFE00, 0xBFFFFFDF, 0xFFFE07FF, 0xFFFFFFFF,
		0x0000EFC7, 0xFFFFFF80, 0x00027FFF, 0xFFFFE000, 0x07F3C05F,
		0x1FF00000, 0xFFFFFF00, 0xFFFFFFFF, 0xFFFFFFFF, 0x001FFF01,
		0x00F80000, 0x8FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF7FAFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFCDFFF, 0xFFFFFFFF,
		0xFDFFFFFF, 0xFFFFFFFF, 0xF7FFFFFF, 0x6FFFFFFF, 0xFF7FFFFF,
		0xDFFFFFFF, 0xFFFFDF7F, 0xFFFFFFFF, 0xFFFFFFE7, 0xFFFFFFFF,
		0xFFCFFFFF, 0x8FFFFF3F, 0xFFFFFFFF, 0xFFFE7FFF, 0xF8DFFFFF,
		0x7F01FFFF, 0xFF807FBC, 0xFFFFF3FF, 0xFFFFFFFF, 0xFFFCFFBF,
		0xFFFFFFFF, 0xFFFFFCFF, 0xFFFFFFFF, 0xFDFF0001, 0xFFE39CC7,
		0x0017FFFF, 0x7FFFFFFF, 0xFFFFFFFC, 0xFFFCFFFF, 0x7E7FF9E7,
		0xFF9C7EF7, 0xFFFFFFFF, 0xFFFFFEFF, 0xF8E3E6FF, 0xFFFFFFFF,
		0xFEFFFFF7, 0xFF3CFFFF, 0x081FFFFF, 0xDFFFFFFC, 0xFFE7FFFF,
		0x39FFDFFF, 0xFFFFC090, 0xF9FFFFFF, 0xFFFFFFFF, 0xFE3FFFFF,
		0x1FF39FBF, 0xFFFFFE00, 0xBFFFFFDF, 0xFFFE07FF, 0xFFFFFFFF,
		0x0000EFC7, 0xFF807F80, 0x00027BFF, 0xFFFFE000, 0x07F3C05F,
		0x1FF00000, 0xFFFFFC00, 0xFFFFFFFF, 0xFFFFFFF9, 0x00039C01,
		0x00100000, 0x8FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF7FAFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFCDFFF, 0xFFFFFFFF,
		0xFDFFFFFF, 0xFFFFFFFF, 0xF7FFFFFF, 0x6FFFFFFF, 0xFF7FFFFF,
		0xDFFFFFFF, 0xFFFFFF7F, 0xFFFFFFFF, 0xFFFFFFE7, 0xFFFFFFFF,
		0xFFCFFFFF, 0x8FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF8DFFFFF,
		0xFFFFFFFF, 0xFFFFE07F, 0x0002737F, 0x0CC3C000, 0x03E0003E,
		0x00200000, 0x00000000, 0x00000000, 0x01FF0000, 0xFFEFFF3C,
		0x07FFFFFF, 0x70000000,
	};
	
	// All the flags for a caught Pokedex
	static const u32 Caught[] = 
	{
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	
	void Category1(MenuEntry *entry)
	{
		static u32 Address = 0x330124A8;
		
		u16& KBValue = *GetArg<u16>(entry);
		Keyboard KB("Medicine:\n\n\n" << Color::Orange << "This will not only modify the Medicine quantities\nbut it will also unlock all Medcines!");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(3);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u16 Input = *static_cast<const u16 *>(In);
			
			if (Input >= 0 && Input <= 999)
				return (true);
			
			Error = "The value must be between 0-999.";
			return (false);
		});
		
		static u16 SavedValue;
		
		if (KB.Open(KBValue, SavedValue) != -1) // Make sure the user didn't abort the keyboard
		{
			if (KBValue >= 0 && KBValue <= 999) 
			{
				int i = 0;
				
                // Add Medicines to pouch and set quantity
                for (i; i < SizeOfCategory1; i++)
				{
                    if (!WRITE32(Address + (i * 4), Category1IDs[i] + (KBValue << 10)))
						goto Error;
                }
				
                // Write empty spaces to rest of pouch to remove any duplicates
                for (i; i < 60; i++)
				{
                    if (!WRITE32(Address + (i * 4), 0x0))
						goto Error;
                }
				
				MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
		
		else MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		SavedValue = KBValue;
		Error: return;
	}
	
	void Category2(MenuEntry *entry)
	{
		static u32 Address = 0x33011934;
		
		u16& KBValue = *GetArg<u16>(entry);
		Keyboard KB("Items:\n\n\n" << Color::Orange << "This will not only modify the Item quantities but\nit will also unlock all Items!");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(3);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u16 Input = *static_cast<const u16 *>(In);
			
			if (Input >= 0 && Input <= 999)
				return (true);
			
			Error = "The value must be between 0-999.";
			return (false);
		});
		
		static u16 SavedValue;
		
		if (KB.Open(KBValue, SavedValue) != -1) // Make sure the user didn't abort the keyboard
		{
			if (KBValue >= 0 && KBValue <= 999) 
			{
				int i = 0;
				
                // Add Items to pouch and set quantity
                for (i; i < SizeOfCategory2; i++)
				{
                    if (!WRITE32(Address + (i * 4), Category2IDs[i] + (KBValue << 10)))
						goto Error;
                }
				
				// Write empty spaces to rest of pouch to remove any duplicates
				for (i; i < 427; i++)
				{
					if (!WRITE32(Address + (i * 4), 0x0))
						goto Error;
				}
				
				MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
		
		else MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		SavedValue = KBValue;
		Error: return;
	}
	
	void Category3(MenuEntry *entry)
	{
		static u32 Address = 0x330122F8;
		
		if (MessageBox("Would you like to unlock all TMs & HMs?", DialogType::DialogYesNo).SetClear(ClearScreen::Both)())
		{
			int i = 0;
			
			// Add TMs & HMs to pouch and set quantity
			for (i; i < SizeOfCategory3; i++)
			{
				if (!WRITE32(Address + (i * 4), Category3IDs[i] + (1 << 10)))
					goto Error;
			}
			
			// Write empty spaces to rest of pouch to remove any duplicates
			for (i; i < 108; i++)
			{
				if (!WRITE32(Address + (i * 4), 0x0))
					goto Error;
			}
			
			MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		}
		
		else MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		Error: return;
	}
	
	void Category4(MenuEntry *entry)
	{
		static u32 Address = 0x33012598;
		
		u16& KBValue = *GetArg<u16>(entry);
		Keyboard KB("Berries:\n\n\n" << Color::Orange << "This will not only modify the Berry quantities\nbut it will also unlock all Berries!");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(3);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u16 Input = *static_cast<const u16 *>(In);
			
			if (Input >= 0 && Input <= 999)
				return (true);
			
			Error = "The value must be between 0-999.";
			return (false);
		});
		
		static u16 SavedValue;
		
		if (KB.Open(KBValue, SavedValue) != -1) // Make sure the user didn't abort the keyboard
		{
			if (KBValue >= 0 && KBValue <= 999) 
			{
				int i = 0;
				
                // Add Items to pouch and set quantity
                for (i; i < SizeOfCategory4; i++)
				{
                    if (!WRITE32(Address + (i * 4), Category4IDs[i] + (KBValue << 10)))
						goto Error;
                }
				
				// Write empty spaces to rest of pouch to remove any duplicates
				for (i; i < 67; i++)
				{
					if (!WRITE32(Address + (i * 4), 0x0))
						goto Error;
				}
				
				MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
		
		else MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		SavedValue = KBValue;
		Error: return;
	}
	
	void Category5(MenuEntry *entry)
	{
		static u32 Address = 0x33011FE0;
		
		if (MessageBox("Would you like to unlock all Key Items?", DialogType::DialogYesNo).SetClear(ClearScreen::Both)())
		{
			int i = 0;
			
			// Add Key Items to pouch and set quantity
			for (i; i < SizeOfCategory5; i++)
			{
				if (!WRITE32(Address + (i * 4), Category5IDs[i] + (1 << 10)))
					goto Error;
			}
			
			MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		}
		
		else MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		Error: return;
	}
	
	void Category6(MenuEntry *entry)
	{
		static u32 Address = 0x330126A4;
		
		if (MessageBox("Would you like to unlock all Z-Crystals?", DialogType::DialogYesNo).SetClear(ClearScreen::Both)())
		{
			int i = 0;
			
			// Add Z-Crystals to pouch and set quantity
			for (i; i < SizeOfCategory6; i++)
			{
				if (!WRITE32(Address + (i * 4), Category6IDs[i] + (1 << 10)))
					goto Error;
			}
			
			MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		}
		
		else MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		Error: return;
	}
	
	void GetMoney(MenuEntry *entry)
	{
		u32& KBValue = *GetArg<u32>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(7);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u32 Input = *static_cast<const u32 *>(In);
			
			if (Input >= 0 && Input <= 9999999)
				return (true);
			
			Error = "The value must be between 0-9999999.";
			return (false);
		});
		
		static u32 SavedValue;
		
		if (entry->IsActivated())
			KB.Open(KBValue, SavedValue);
		
		SavedValue = KBValue;
	}
	
	void SetMoney(MenuEntry *entry)
	{
		static u32 Address = 0x33015210;
		
		u32& KBValue = *GetArg<u32>(entry);
		WRITE32(Address, KBValue);
	}
	
	void GetBattlePoints(MenuEntry *entry)
	{
		u16& KBValue = *GetArg<u16>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(4);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u16 Input = *static_cast<const u16 *>(In);
			
			if (Input >= 0 && Input <= 9999)
				return (true);
			
			Error = "The value must be between 0-9999.";
			return (false);
		});
		
		static u16 SavedValue;
		
		if (entry->IsActivated())
			KB.Open(KBValue, SavedValue);
		
		SavedValue = KBValue;
	}
	
	void SetBattlePoints(MenuEntry *entry)
	{
		static u32 Address = 0x33015328;
		
		u16& KBValue = *GetArg<u16>(entry);
		WRITE16(Address, KBValue);
	}
	
	void GetFestivalCoins(MenuEntry *entry)
	{
		u32& KBValue = *GetArg<u32>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(7);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u32 Input = *static_cast<const u32 *>(In);
			
			if (Input >= 0 && Input <= 9999999)
				return (true);
			
			Error = "The value must be between 0-9999999.";
			return (false);
		});
		
		static u32 SavedValue;
		
		if (entry->IsActivated())
			KB.Open(KBValue, SavedValue);
		
		SavedValue = KBValue;
	}
	
	void SetFestivalCoins(MenuEntry *entry)
	{
		static u32 Address = 0x33061168;
		
		u32& KBValue = *GetArg<u32>(entry);
		WRITE32(Address, KBValue);
	}
	
	void GetPokedex(MenuEntry *entry)
	{
		if (!entry->IsActivated())
		{
			int& KBValue = *GetArg<int>(entry);
			std::vector<std::string> KBOptions = {"Seen", "Obtained"};
			Keyboard KB(entry->Name() + ":");
			KB.Populate(KBOptions);
			KBValue = KB.Open();
			
			if (KBValue < 0) // If the user has aborted the keyboard
			{
				MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
				return;
			}
			
			if (KBValue == 0) // Seen
			{
				Process::CopyMemory((void *)(0x33013DF4), Seen, 0x2C0);
				MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
			
			if (KBValue == 1) // Caught
			{
				Process::CopyMemory((void *)(0x33013D90), Caught, 0x60);
				MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
	}
	
	void SetPokedex(MenuEntry *entry)
	{
		if (entry->Hotkeys[0].IsDown())
		{
			// Checks to see if the Pokedex has already been unlocked or i
			if (READ16(0x330138CF, g_Data16) && (g_Data16 & ~0xFF0F) != 0x30)
			{
				READ8(0x330138CF, g_Data8);
				g_Data8 &= 0x0F;
				g_Data8 += 0x30;
				WRITE8(0x330138CF, g_Data8);
			}
			
			if (READ16(0x330138CF, g_Data16) && (g_Data16 & ~0xFF0F) == 0x30)
			{
				// Unlocks the other Pokedex elements once the Pokedex has been unlocked
				if (READ16(0x330138D8, g_Data16) && (g_Data16 & ~0xFFF0) != 0x07)
				{
					READ8(0x330138D8, g_Data8);
					g_Data8 &= 0xF0;
					g_Data8 += 0x07;
					WRITE8(0x330138D8, g_Data8);
				}
			}
		}
	}
	
	void Nickname(MenuEntry *entry)
	{
		static u32 Address = 0x33012850;
		
		std::string& KBValue = *GetArg<std::string>(entry);
		static std::string SavedValue;
		KB<std::string>(entry->Name() + ":", true, false, 12, KBValue, SavedValue);
		SavedValue = KBValue;
		
		if (!Controller::IsKeyPressed(Key::B))
			Process::WriteString(Address, KBValue, StringFormat::Utf16);
	}
	
	void GetPlaytime(MenuEntry *entry)
	{
		Keyboard KB1("Hours:");
		KB1.IsHexadecimal(false);
		KB1.SetMaxLength(3);
		KB1.SetCompareCallback([](const void *In, std::string &Error)
		{
			u16 Input = *static_cast<const u16 *>(In);
			
			if (Input >= 0 && Input <= 999)
				return (true);
			
			Error = "The value must be between 0-999.";
			return (false);
		});
		
		static u16 SavedValue1;
		KB1.Open(Value1, SavedValue1);
		SavedValue1 = Value1;
		
		if (!Controller::IsKeyPressed(Key::B))
		{
			Keyboard KB2("Minutes:");
			KB2.IsHexadecimal(false);
			KB2.SetMaxLength(2);
			KB2.SetCompareCallback([](const void *In, std::string &Error)
			{
				u8 Input = *static_cast<const u8 *>(In);
				
				if (Input >= 0 && Input <= 59)
					return (true);
				
				Error = "The value must be between 0-59.";
				return (false);
			});
			
			static u8 SavedValue2;
			KB2.Open(Value2, SavedValue2);
			SavedValue2 = Value2;
			
			if (!Controller::IsKeyPressed(Key::B))
			{
				Keyboard KB3("Seconds:");
				KB3.IsHexadecimal(false);
				KB3.SetMaxLength(2);
				KB3.SetCompareCallback([](const void *In, std::string &Error)
				{
					u8 Input = *static_cast<const u8 *>(In);
					
					if (Input >= 0 && Input <= 59)
						return (true);
					
					Error = "The value must be between 0-59.";
					return (false);
				});
				
				static u8 SavedValue3;
				KB3.Open(Value3, SavedValue3);
				SavedValue3 = Value3;
				
				if (!Controller::IsKeyPressed(Key::B))
				{
					Playtime = 0x33F8127C;
					entry->Enable();
					MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
				}
			}
		}
		
		if (Controller::IsKeyPressed(Key::B))
		{
			Playtime = 0;
			entry->Disable();
			MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		}
	}
	
	void SetPlaytime(MenuEntry *entry)
	{
		WRITE16(Playtime, Value1);
		WRITE16(Playtime + 0x2, Value2 | (Value3 << 8));
	}
	
	void Identity1(MenuEntry *entry)
	{
		static u32 Address = 0x3301281A;
		
		u16 SID; READ16(Address, SID);
		u16 TID; READ16(Address = 0x2, TID);
		
		u32 IDN = TID + (SID * 65536) % 1000000;
		
		u32& KBValue = *GetArg<u32>(entry);
		Keyboard KB(entry->Name() + ":\n\n" << Color::Orange << "SID" << Color::White << ": " << std::to_string(SID) << Color::Orange << " TID" << Color::White << ": " << std::to_string(TID) << Color::Orange << " ID No" << Color::White << ": " << std::to_string(IDN));
		KB.IsHexadecimal(false);
		KB.SetMaxLength(5);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u32 Input = *static_cast<const u32 *>(In);
			
			if (Input >= 1 && Input <= 65535)
				return (true);
			
			Error = "The value must be between 1-65535.";
			return (false);
		});
		
		static u16 SavedValue;
		
		if (KB.Open(KBValue, SavedValue) != -1)
		{
			if (KBValue >= 1 && KBValue <= 65535)
				WRITE16(Address, KBValue);
		}
		
		SavedValue = KBValue;
	}
	
	void Identity2(MenuEntry *entry)
	{
		static u32 Address = 0x3301281A;
		
		u16 SID; READ16(Address, SID);
		u16 TID; READ16(Address - 0x2, TID);
		
		u32 IDN = TID + (SID * 65536) % 1000000;
		
		u32& KBValue = *GetArg<u32>(entry);
		Keyboard KB(entry->Name() + ":\n\n" << Color::Orange << "SID" << Color::White << ": " << std::to_string(SID) << Color::Orange << " TID" << Color::White << ": " << std::to_string(TID) << Color::Orange << " ID No" << Color::White << ": " << std::to_string(IDN));
		KB.IsHexadecimal(false);
		KB.SetMaxLength(5);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u32 Input = *static_cast<const u32 *>(In);
			
			if (Input >= 1 && Input <= 65535)
				return (true);
			
			Error = "The value must be between 1-65535.";
			return (false);
		});
		
		static u16 SavedValue;
		
		if (KB.Open(KBValue, SavedValue) != -1)
		{
			if (KBValue >= 1 && KBValue <= 65535)
				WRITE16(Address - 0x2, KBValue);
		}
		
		SavedValue = KBValue;
	}
	
	void GetLanguage(MenuEntry *entry)
	{
		int& KBValue = *GetArg<int>(entry);
		
		const KBSelection KBArray[7] = 
		{
			{"English", 0x2},
			{"French", 0x3},
			{"German", 0x5},
			{"Italian", 0x4},
			{"Japanese", 0x1}, 
			{"Korean", 0x7},
			{"Spanish", 0x6}
		};
		
		std::vector<std::string> KBOptions;
		
		for (const KBSelection& KBName:KBArray)
			KBOptions.push_back(KBName.Name);
		
		Keyboard KB(entry->Name() + ":");
		KB.Populate(KBOptions);
		
		if (entry->IsActivated())
			KBValue = KBArray[KB.Open()].Value;
    }
	
	void SetLanguage(MenuEntry *entry)
	{
		static u32 Address = 0x3301284D;
		
		int& KBValue = *GetArg<int>(entry);
		
		if (KBValue >= 0x1 && KBValue <= 7)
			WRITE8(Address, KBValue);
	}
	
	void TimeOfDay(MenuEntry *entry)
	{
		static u32 Address = 0x330154B0;
		
		u32 Time = 0;
		Keyboard KB("Time of Day:\n\nChoose an offset between 1-24 hours\n\n" << Color::SkyBlue << "12H" << Color::White << " - Moon" << Color::Orange << " 24H" << Color::White << " - Sun");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(2);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u32 Input = *static_cast<const u32 *>(In);
			
			if (Input >= 1 && Input <= 24)
				return (true);
			
			Error = "The value must be between 1-24.";
			return (false);
		});
		
		if (!READ32(Address, Time))
			goto Error;
		
		Time /= 3600;
		
		if (KB.Open(Time, Time) != -1)
		{
			if (Time >= 1 || Time <= 24)
			{
				if (!WRITE32(Address, Time * 3600))
					goto Error;
			}
		}
		
		Error: return;
	}
}