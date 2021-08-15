#include "CTRPluginFramework.hpp"

#include "../../Helpers/KeyboardHelpers.hpp"
#include "../../Helpers.hpp"

using namespace CTRPluginFramework;

namespace ORAS
{
	static u32 Playtime; static u16 Value1; static u8 Value2, Value3;
	
	#define SizeOfCategory1 sizeof(Category1IDs) / sizeof(Category1IDs[0])
	#define SizeOfCategory2 sizeof(Category2IDs) / sizeof(Category2IDs[0])
	#define SizeOfCategory3 sizeof(Category3IDs) / sizeof(Category3IDs[0])
	#define SizeOfCategory4 sizeof(Category4IDs) / sizeof(Category4IDs[0])
	#define SizeOfCategory5 sizeof(Category5IDs) / sizeof(Category5IDs[0])
	
	// All the Item IDs
	static int Category1IDs[] =
	{
		1, 2, 3, 4, 5, 6, 7, 8, 9,
		
		10, 11, 12, 13, 14, 15, 16, 55, 56, 57, 58, 59, 60, 61, 62,
		63, 64, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
		81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 99,
		
		100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 112,
		116, 117, 118, 119, 135, 136, 213, 214, 215, 217, 218, 219,
		220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231,
		232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243,
		244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
		256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267,
		268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279,
		280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291,
		292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303,
		304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315,
		316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327,
		492, 493, 494, 495, 496, 497, 498, 499, 500, 537, 538, 539,
		540, 541, 542, 543, 544, 545, 546, 547, 548, 549, 550, 551,
		552, 553, 554, 555, 556, 557, 558, 559, 560, 561, 562, 563,
		564, 571, 572, 573, 576, 577, 580, 581, 582, 583, 584, 585,
		586, 587, 588, 589, 590, 639, 640, 644, 646, 647, 648, 649,
		650, 652, 653, 654, 655, 656, 657, 658, 659, 660, 661, 662,
		663, 664, 665, 666, 667, 668, 669, 670, 671, 672, 673, 674,
		675, 676, 677, 678, 679, 680, 681, 682, 683, 684, 685, 699,
		704, 710, 711, 715, 534, 535, 752, 753, 754, 755, 756, 757,
		758, 759, 760, 761, 762, 763, 764, 767, 768, 769, 770
	};
	
	// All the Medicine IDs
	static int Category2IDs[] = 
	{
		17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
		32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46,
		47, 48, 49, 50, 51, 52, 53, 54,
		
		134, 504, 565, 566, 567, 568, 569, 570, 571, 591, 645, 708,
		709,
		
		65, 66, 67
	};
	
	// All the TM & HM IDs
	static int Category3IDs[] =
	{
		328, 329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339,
		340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351,
		352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363,
		364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375,
		376, 377, 378, 379, 380, 381, 382, 383, 384, 385, 386, 387,
		388, 389, 390, 391, 392, 393, 394, 395, 396, 397, 398, 399,
		400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411,
		412, 413, 414, 415, 416, 417, 418, 419, 618, 619, 620, 690,
		691, 692, 693, 694, 420, 421, 422, 423, 424, 425, 737
	};
	
	// All the Berry IDs
	static int Category4IDs[] =
	{
		149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160,
		161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
		173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184,
		185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196,
		197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208,
		209, 210, 211, 212, 686, 687, 688
	};
	
	// All the Key Item IDs
	static int Category5IDs[] =
	{
		216, 445, 446, 447, 465, 466, 471, 628, 629, 631, 632, 638,
		697, 457, 474, 503, 718, 719, 720, 721, 722, 724, 725, 726,
		727, 728, 729, 730, 731, 732, 733, 734, 735, 736, 738, 739,
		740, 741, 742, 743, 744, 751, 765, 771, 772, 774, 775
	};
	
	// All the flags for a seen Pokedex. Took forever lol...
	static const u8 Seen[] =
	{
		0xFF, 0xFF, 0xFF, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFA, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7,
		0xFF, 0xFF, 0xFF, 0x6F, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF,
		0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8F,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0x7F, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFF,
		0xE7, 0xF9, 0x7F, 0x7E, 0xF7, 0x7E, 0x9C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xE6, 0xE3, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF,
		0xF7, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0x3C, 0xFF, 0xFF, 0xFF, 0x1F, 0x08,
		0xFC, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xE7, 0xFF, 0xFF, 0xDF, 0xFF, 0x39,
		0x90, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0x3F, 0xFE, 0xBF, 0x9F, 0xF3, 0x1F, 0x00, 0xFE, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xBF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFA, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xFC, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7,
		0xFF, 0xFF, 0xFF, 0x6F, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF,
		0x7F, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCF, 0xFF, 0x3F, 0xFF, 0xFF, 0x8F,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0x7F, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFF,
		0xE7, 0xF9, 0x7F, 0x7E, 0xF7, 0x7E, 0x9C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xE6, 0xE3, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF,
		0xF7, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0x3C, 0xFF, 0xFF, 0xFF, 0x1F, 0x08,
		0xFC, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xE7, 0xFF, 0xFF, 0xDF, 0xFF, 0x39,
		0x90, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0x3F, 0xFE, 0xBF, 0x9F, 0xF3, 0x1F, 0x00, 0xFE, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xBF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFA, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7,
		0xFF, 0xFF, 0xFF, 0x6F, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF,
		0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8F,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	
	// All the flags for a caught Pokedex
	static const u8 Caught[] =
	{
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	
	void Category1(MenuEntry *entry)
	{
		static u32 Address = 0x8C6EC70;
		
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
			if (KBValue >= 0 && KBValue <= 999) // Make sure that the value is between 0 and 999
			{
				int i = 0;
				
				for (int j = 0; j < SizeOfCategory1; j++) // Loops x amount of times depending on the size of the IDs. Must loop through all of them
				{
					WRITE16(Address + (i * 4), Category1IDs[j]); // Must get through all the IDs
					WRITE16((Address + 0x2) + (i * 4), KBValue); // Writes the quantity of the IDs
					i++;
				}
				
				MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
		
		else MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		SavedValue = KBValue;
	}
	
	void Category2(MenuEntry *entry)
	{
		static u32 Address = 0x8C6F5E0;
		
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
			if (KBValue >= 0 && KBValue <= 999) // Make sure that the value is between 0 and 999
			{
				int i = 0;
				
				for (int j = 0; j < SizeOfCategory2; j++) // Loops x amount of times depending on the size of the IDs. Must loop through all of them
				{
					WRITE16(Address + (i * 4), Category2IDs[j]); // Must get through all the IDs
					WRITE16((Address + 0x2) + (i * 4), KBValue); // Writes the quantity of the IDs
					i++;
				}
				
				MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			} 
		}
		
		else MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		SavedValue = KBValue;
	}
	
	void Category3(MenuEntry *entry)
	{
		static u32 Address = 0x8C6F430;
		
		int i = 0;
		
		if (MessageBox("Would you like to unlock all TMs & HMs?", DialogType::DialogYesNo).SetClear(ClearScreen::Both)())
		{
			for (int j = 0; j < SizeOfCategory3; j++) // Loops x amount of times depending on the size of the IDs. Must loop through all of them
			{
				WRITE16(Address + (i * 4), Category3IDs[j]); // Must get through all the IDs
				WRITE16((Address + 0x2) + (i * 4), 0x1);
				i++;
			}
			
			MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		}
		
		else MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
	}
	
	void Category4(MenuEntry *entry)
	{
		static u32 Address = 0x8C6F6E0;
		
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
			if (KBValue >= 0 && KBValue <= 999) // Make sure that the value is between 0 and 999
			{
				int i = 0;
				
				for (int j = 0; j < SizeOfCategory4; j++) // Loops x amount of times depending on the size of the IDs. Must loop through all of them
				{
					WRITE16(Address + (i * 4), Category4IDs[j]); // Must get through all the IDs
					WRITE16((Address + 0x2) + (i * 4), KBValue); // Writes the quantity of the IDs
					i++;
				}
				
				MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
		
		else MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		SavedValue = KBValue;
	}
	
	void Category5(MenuEntry *entry)
	{
		static u32 Address = 0x8C6F2B0;
		
		int i = 0;
		
		if (MessageBox("Would you like to unlock all Key Items?", DialogType::DialogYesNo).SetClear(ClearScreen::Both)())
		{
			for (int j = 0; j < SizeOfCategory5; j++) // Loops x amount of times depending on the size of the IDs. Must loop through all of them
			{
				WRITE16(Address + (i * 4), Category5IDs[j]); // Must get through all the IDs
				WRITE16((Address + 0x2) + (i * 4), 0x1);
				i++;
			}
			
			MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		}
		
		else MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
	}
	
	void GetMiles(MenuEntry *entry)
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
	
	void SetMiles(MenuEntry *entry)
	{
		static u32 Address = 0x8C8B36C;
		
		u32& KBValue = *GetArg<u32>(entry);
		WRITE32(Address, KBValue);
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
		static u32 Address = 0x8C71DC0;
		
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
		static u32 Address = 0x8C71DE8;
		
		u16& KBValue = *GetArg<u16>(entry);
		WRITE16(Address, KBValue);
	}
	
	void GetPokedex(MenuEntry *entry)
	{
		static u32 Address[2] =
		{
			0x8C8204C,
			0x8C81FEC
		};
		
		if (!entry->IsActivated())
		{
			int& KBValue = *GetArg<int>(entry);
			
			std::vector<std::string> KBOptions =
			{
				"Seen",
				"Obtained"
			};
			
			Keyboard KB(entry->Name() + ":");
			KB.Populate(KBOptions);
			KBValue = KB.Open();
			
			if (KBValue < 0) // If the user has aborted the keyboard
			{
				MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
				return;
			}
			
			if (!entry->IsActivated() && KBValue == 0) // Seen
			{
				Process::CopyMemory((void *)(Address[0]), Seen, 0x1D0);
				MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
			
			else if (!entry->IsActivated() && KBValue == 1) // Caught
			{
				Process::CopyMemory((void *)(Address[1]), Caught, 0x60);
				MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
		}
	}
	
	void SetPokedex(MenuEntry *entry)
	{
		static u32 Address[2] =
		{
			0x8C81F20,
			0x8C81FE8
		};
		
		// If the hotkey is pressed down
		if (entry->Hotkeys[0].IsDown())
		{
			// Checks to see if the Pokedex has already been unlocked or not
			if (READ16(Address[0], g_Data16) && (g_Data16 & ~0xFFF0) != 0x05)
			{
				READ8(Address[0], g_Data8);
				g_Data8 &= 0xF0;
				g_Data8 += 0x05;
				WRITE8(Address[0], g_Data8);
			}
			
			// Otherwise if it is, then the user may unlock the other Pokedex elements as well
			else if (READ16(Address[0], g_Data16) && (g_Data16 & ~0xFFF0) == 0x05)
			{
				if (READ16(Address[1], g_Data16) && (g_Data16 & ~0xFFF0) != 0x09)
				{
					READ8(Address[1], g_Data8);
					g_Data8 &= 0xF0;
					g_Data8 += 0x09;
					WRITE8(Address[1], g_Data8);
				}
			}
		}
	}
	
	void Nickname(MenuEntry *entry)
	{
		static u32 Address = 0x8C81388;
		
		std::string& KBValue = *GetArg<std::string>(entry);
		static std::string SavedValue;
		KB<std::string>(entry->Name() + ":", true, false, 16, KBValue, SavedValue);
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
					Playtime = 0x8CFBD88;
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
		static u32 Address = 0x8C81342;
		
		u32& KBValue = *GetArg<u32>(entry);
		Keyboard KB(entry->Name() + ":");
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
		
		if (KB.Open(KBValue, SavedValue) != -1) // Make sure the user didn't abort the keyboard 
		{
			if (KBValue >= 1 && KBValue <= 65535) 
				WRITE16(Address, KBValue);
		}
		
		SavedValue = KBValue;
	}
	
	void Identity2(MenuEntry *entry)
	{
		static u32 Address = 0x8C81340;
		
		u32& KBValue = *GetArg<u32>(entry);
		Keyboard KB(entry->Name() + ":");
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
		
		if (KB.Open(KBValue, SavedValue) != -1) // Make sure the user didn't abort the keyboard 
		{
			if (KBValue >= 1 && KBValue <= 65535) 
				WRITE16(Address, KBValue);
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
		static u32 Address = 0x8C8136D;
		
		int& KBValue = *GetArg<int>(entry);
		
		if (KBValue >= 0x1 && KBValue <= 7)
			WRITE8(Address, KBValue);
	}
	
	void GymBadges(MenuEntry *entry)
	{
		static u32 Address = 0x8C71DC4l;
		static const u8 Check[8] = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};
		
		int& KBValue = *GetArg<int>(entry);
		
		std::vector<std::string> KBOptions = 
		{
			"Badge 1", 
			"Badge 2", 
			"Badge 3", 
			"Badge 4", 
			"Badge 5", 
			"Badge 6", 
			"Badge 7", 
			"Badge 8"
		};
		
		Keyboard KB(entry->Name() + ":");
		KB.Populate(KBOptions, false);
		KBValue = KB.Open();
		
		if (KBValue < 0)
			return;
		
		if (KBValue < 4) 
		{
			if (READ16(Address, g_Data16) && (g_Data16 & ~0xFFF0) < Check[KBValue])
			{
				READ8(Address, g_Data8);
				g_Data8 &= 0xF0;
				g_Data8 += Check[KBValue];
				WRITE8(Address, g_Data8);
				OSD::Notify(Color::Yellow << "Notice! " << Color::White << "Unlocked Gym Badges: " << std::to_string(KBValue + 1));
			}
			
			else MessageBox("You already have already unlocked that Gym Badge, thus, there is no point in unlocking the Gym Badge once again!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		}
		
		else
		{
			if (READ16(Address, g_Data16) && (g_Data16 & ~0xFF00) < Check[KBValue])
			{
				READ8(Address, g_Data8);
				g_Data8 &= 0x0;
				g_Data8 += Check[KBValue];
				WRITE8(Address, g_Data8);
				OSD::Notify(Color::Yellow << "Notice! " << Color::White << "Unlocked Gym Badges: " << std::to_string(KBValue + 1));
			}
			
			else MessageBox("You already have already unlocked that Gym Badge, thus, there is no point in unlocking the Gym Badge once again!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		}
	}
}