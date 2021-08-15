#include "CTRPluginFramework.hpp"

#include "../../Helpers/KeyboardHelpers.hpp"
#include "../../Helpers.hpp"

using namespace CTRPluginFramework;

namespace ORAS
{
	static const std::vector<u32> PartyPointer1 = 
	{
		0x81FB58C, // Slot 1
		0x81FB590, // Slot 2
		0x81FB594, // Slot 3
		0x81FB598, // Slot 4
		0x81FB59C, // Slot 5
		0x81FB5A0  // Slot 6
	};
	
	static const std::vector<u32> PartyPointer2 = 
	{
		0x81FB92C, // Slot 1
		0x81FB930, // Slot 2
		0x81FB934, // Slot 3
		0x81FB938, // Slot 4
		0x81FB94C, // Slot 5
		0x81FB950  // Slot 6
	};
	
	static const std::vector<u32> EnemyPointer1 = 
	{
		0x81FB5A8, // Slot 1
		0x81FB5AC, // Slot 2
		0x81FB5B0, // Slot 3
		0x81FB5B4, // Slot 4
		0x81FB5B8, // Slot 5
		0x81FB5BC, // Slot 6
	};
	
	static const std::vector<u32> EnemyPointer2 = 
	{
		0x81FB948, // Slot 1
		0x81FB94C, // Slot 2
		0x81FB950, // Slot 3
		0x81FB954, // Slot 4
		0x81FB958, // Slot 5
		0x81FB95C  // Slot 6
	};
	
	bool IsOnline = System::IsConnectedToInternet();
	
	bool IsInBattle(void)
	{
		static u32 Pointer = 0x81FB478;
		
		// Reads the pointer and if its data is 0x40001, then is in battle. It also must be offline to return true
		if (READ32(Pointer, g_Data32) && g_Data32 == 0x40001 && !IsOnline)
			return true;
		
		else return false;
	}
	
	void GetAttackStat(MenuEntry *entry)
	{
		u16& KBValue = *GetArg<u16>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(3);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u16 Input = *static_cast<const u16 *>(In);
			
			if (Input >= 1 && Input <= 999)
				return (true);
			
			Error = "The value must be between 1-999.";
			return (false);
		});
		
		static u16 SavedValue;
		
		if (entry->IsActivated())
			KB.Open(KBValue, SavedValue);
		
		SavedValue = KBValue;
	}
	
	void SetAttackStat(MenuEntry *entry)
	{
		u16& KBValue = *GetArg<u16>(entry);
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			if (KBValue >= 0x1)
			{
				for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
				{
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0xF6, KBValue);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0xF6, KBValue);
					}
				}
			}
		}
	}
	
	void GetDefenseStat(MenuEntry *entry)
	{
		u16& KBValue = *GetArg<u16>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(3);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u16 Input = *static_cast<const u16 *>(In);
			
			if (Input >= 1 && Input <= 999)
				return (true);
			
			Error = "The value must be between 1-999.";
			return (false);
		});
		
		static u16 SavedValue;
		
		if (entry->IsActivated())
			KB.Open(KBValue, SavedValue);
		
		SavedValue = KBValue;
	}
	
	void SetDefenseStat(MenuEntry *entry)
	{
		u16& KBValue = *GetArg<u16>(entry);
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			if (KBValue >= 0x1)
			{
				for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
				{
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0xF8, KBValue);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0xF8, KBValue);
					}
				}
			}
		}
	}
	
	void GetSpAtkStat(MenuEntry *entry)
	{
		u16& KBValue = *GetArg<u16>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(3);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u16 Input = *static_cast<const u16 *>(In);
			
			if (Input >= 1 && Input <= 999)
				return (true);
			
			Error = "The value must be between 1-999.";
			return (false);
		});
		
		static u16 SavedValue;
		
		if (entry->IsActivated())
			KB.Open(KBValue, SavedValue);
		
		SavedValue = KBValue;
	}
	
	void SetSpAtkStat(MenuEntry *entry)
	{
		u16& KBValue = *GetArg<u16>(entry);
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			if (KBValue >= 0x1)
			{
				for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
				{
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0xFA, KBValue);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0xFA, KBValue);
					}
				}
			}
		}
	}
	
	void GetSpDefStat(MenuEntry *entry)
	{
		u16& KBValue = *GetArg<u16>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(3);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u16 Input = *static_cast<const u16 *>(In);
			
			if (Input >= 1 && Input <= 999)
				return (true);
			
			Error = "The value must be between 1-999.";
			return (false);
		});
		
		static u16 SavedValue;
		
		if (entry->IsActivated())
			KB.Open(KBValue, SavedValue);
		
		SavedValue = KBValue;
	}
	
	void SetSpDefStat(MenuEntry *entry)
	{
		u16& KBValue = *GetArg<u16>(entry);
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			if (KBValue >= 0x1)
			{
				for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
				{
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0xFC, KBValue);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0xFC, KBValue);
					}
				}
			}
		}
	}
	
	void GetSpeedStat(MenuEntry *entry)
	{
		u16& KBValue = *GetArg<u16>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(3);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u16 Input = *static_cast<const u16 *>(In);
			
			if (Input >= 1 && Input <= 999)
				return (true);
			
			Error = "The value must be between 1-999.";
			return (false);
		});
		
		static u16 SavedValue;
		
		if (entry->IsActivated())
			KB.Open(KBValue, SavedValue);
		
		SavedValue = KBValue;
	}
	
	void SetSpeedStat(MenuEntry *entry)
	{
		u16& KBValue = *GetArg<u16>(entry);
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			if (KBValue >= 0x1)
			{
				for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
				{
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0xFE, KBValue);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0xFE, KBValue);
					}
				}
			}
		}
	}
	
	void GetAttackBoost(MenuEntry *entry)
	{
		u8& KBValue = *GetArg<u8>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(1);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u8 Input = *static_cast<const u8 *>(In);
			
			if (Input >= 0 && Input <= 6)
				return (true);
			
			Error = "The value must be between 0-6.";
			return (false);
		});
		
		static u8 SavedValue;
		
		if (entry->IsActivated())
			KB.Open(KBValue, SavedValue);
		
		SavedValue = KBValue;
	}
	
	void SetAttackBoost(MenuEntry *entry)
	{
		u8& KBValue = *GetArg<u8>(entry);
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
			{
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x104, 0x6 + KBValue);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x104, 0x6 + KBValue);
				}
			}
		}
	}
	
	void GetDefenseBoost(MenuEntry *entry)
	{
		u8& KBValue = *GetArg<u8>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(1);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u8 Input = *static_cast<const u8 *>(In);
			
			if (Input >= 0 && Input <= 6)
				return (true);
			
			Error = "The value must be between 0-6.";
			return (false);
		});
		
		static u8 SavedValue;
		
		if (entry->IsActivated())
			KB.Open(KBValue, SavedValue);
		
		SavedValue = KBValue;
	}
	
	void SetDefenseBoost(MenuEntry *entry)
	{
		u8& KBValue = *GetArg<u8>(entry);
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
			{
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x105, 0x6 + KBValue);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x105, 0x6 + KBValue);
				}
			}
		}
	}
	
	void GetSpAtkBoost(MenuEntry *entry)
	{
		u8& KBValue = *GetArg<u8>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(1);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u8 Input = *static_cast<const u8 *>(In);
			
			if (Input >= 0 && Input <= 6)
				return (true);
			
			Error = "The value must be between 0-6.";
			return (false);
		});
		
		static u8 SavedValue;
		
		if (entry->IsActivated())
			KB.Open(KBValue, SavedValue);
		
		SavedValue = KBValue;
	}
	
	void SetSpAtkBoost(MenuEntry *entry)
	{
		u8& KBValue = *GetArg<u8>(entry);
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
			{
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x106, 0x6 + KBValue);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x106, 0x6 + KBValue);
				}
			}
		}
	}
	
	void GetSpDefBoost(MenuEntry *entry)
	{
		u8& KBValue = *GetArg<u8>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(1);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u8 Input = *static_cast<const u8 *>(In);
			
			if (Input >= 0 && Input <= 6)
				return (true);
			
			Error = "The value must be between 0-6.";
			return (false);
		});
		
		static u8 SavedValue;
		
		if (entry->IsActivated())
			KB.Open(KBValue, SavedValue);
		
		SavedValue = KBValue;
	}
	
	void SetSpDefBoost(MenuEntry *entry)
	{
		u8& KBValue = *GetArg<u8>(entry);
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
			{
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x107, 0x6 + KBValue);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x107, 0x6 + KBValue);
				}
			}
		}
	}
	
	void GetSpeedBoost(MenuEntry *entry)
	{
		u8& KBValue = *GetArg<u8>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(1);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u8 Input = *static_cast<const u8 *>(In);
			
			if (Input >= 0 && Input <= 6)
				return (true);
			
			Error = "The value must be between 0-6.";
			return (false);
		});
		
		static u8 SavedValue;
		
		if (entry->IsActivated())
			KB.Open(KBValue, SavedValue);
		
		SavedValue = KBValue;
	}
	
	void SetSpeedBoost(MenuEntry *entry)
	{
		u8& KBValue = *GetArg<u8>(entry);
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
			{
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x108, 0x6 + KBValue);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x108, 0x6 + KBValue);
				}
			}
		}
	}
	
	void GetAccuracyBoost(MenuEntry *entry)
	{
		u8& KBValue = *GetArg<u8>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(1);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u8 Input = *static_cast<const u8 *>(In);
			
			if (Input >= 0 && Input <= 6)
				return (true);
			
			Error = "The value must be between 0-6.";
			return (false);
		});
		
		static u8 SavedValue;
		
		if (entry->IsActivated())
			KB.Open(KBValue, SavedValue);
		
		SavedValue = KBValue;
	}
	
	void SetAccuracyBoost(MenuEntry *entry)
	{
		u8& KBValue = *GetArg<u8>(entry);
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
			{
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x109, 0x6 + KBValue);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x109, 0x6 + KBValue);
				}
			}
		}
	}
	
	void GetEvasivenessBoost(MenuEntry *entry)
	{
		u8& KBValue = *GetArg<u8>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(1);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u8 Input = *static_cast<const u8 *>(In);
			
			if (Input >= 0 && Input <= 6)
				return (true);
			
			Error = "The value must be between 0-6.";
			return (false);
		});
		
		static u8 SavedValue;
		
		if (entry->IsActivated())
			KB.Open(KBValue, SavedValue);
		
		SavedValue = KBValue;
	}
	
	void SetEvasivenessBoost(MenuEntry *entry)
	{
		u8& KBValue = *GetArg<u8>(entry);
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
			{
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x10A, 0x6 + KBValue);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x10A, 0x6 + KBValue);
				}
			}
		}
	}
	
	void GetType1(MenuEntry *entry)
	{
		int& KBValue = *GetArg<int>(entry);
		
		const KBSelection KBArray[18] = 
		{
			{"Bug", 0x6},
			{"Dark", 0x10},
			{"Dragon", 0xF},
			{"Electric", 0xC},
			{"Fairy", 0x11},
			{"Fighting", 0x1},
			{"Fire", 0x9},
			{"Flying", 0x2},
			{"Ghost", 0x7},
			{"Grass", 0xB},
			{"Ground", 0x4},
			{"Ice", 0xE},
			{"Normal", 0x0},
			{"Poison", 0x3},
			{"Psychic", 0xD},
			{"Rock", 0x5},
			{"Steel", 0x8},
			{"Water", 0xA}
		};
		
		std::vector<std::string> KBOptions;
		
		for (const KBSelection& KBName:KBArray)
			KBOptions.push_back(KBName.Name);
		
		Keyboard KB(entry->Name() + ":");
		KB.Populate(KBOptions, false);
		
		if (entry->IsActivated())
			KBValue = KBArray[KB.Open()].Value;
	}
	
	void SetType1(MenuEntry *entry)
	{
		int& KBValue = *GetArg<int>(entry);
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			if (KBValue >= 0x0 && KBValue <= 0x11)
			{
				for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
				{
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE8(g_Offset32 + 0x100, KBValue);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE8(g_Offset32 + 0x100, KBValue);
					}
				}
			}
		}
	}
	
	void GetType2(MenuEntry *entry)
	{
		int& KBValue = *GetArg<int>(entry);
		
		const KBSelection KBArray[18] = 
		{
			{"Bug", 0x6},
			{"Dark", 0x10},
			{"Dragon", 0xF},
			{"Electric", 0xC},
			{"Fairy", 0x11},
			{"Fighting", 0x1},
			{"Fire", 0x9},
			{"Flying", 0x2},
			{"Ghost", 0x7},
			{"Grass", 0xB},
			{"Ground", 0x4},
			{"Ice", 0xE},
			{"Normal", 0x0},
			{"Poison", 0x3},
			{"Psychic", 0xD},
			{"Rock", 0x5},
			{"Steel", 0x8},
			{"Water", 0xA}
		};
		
		std::vector<std::string> KBOptions;
		
		for (const KBSelection& KBName:KBArray)
			KBOptions.push_back(KBName.Name);
		
		Keyboard KB(entry->Name() + ":");
		KB.Populate(KBOptions, false);
		
		if (entry->IsActivated())
			KBValue = KBArray[KB.Open()].Value;
	}
	
	void SetType2(MenuEntry *entry)
	{
		int& KBValue = *GetArg<int>(entry);
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			if (KBValue >= 0x0 && KBValue <= 0x11)
			{
				for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
				{
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE8(g_Offset32 + 0x101, KBValue);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE8(g_Offset32 + 0x101, KBValue);
					}
				}
			}
		}
	}
	
	void GetAbility(MenuEntry *entry)
	{
		int& KBValue = *GetArg<int>(entry);
		
		const KBSelection KBArray[52] = 
		{
			{"Adaptability", 0x5B},
			{"Aerilate", 0xB8},
			{"Aftermath", 0x6A},
			{"Air Lock", 0x4C},
			{"Aura Break", 0xBC},
			{"Bad Dreams", 0x7B},
			{"Chlorophyll", 0x22},
			{"Clear Body", 0x1D},
			{"Cloud Nine", 0xD},
			{"Color Change", 0x10},
			{"Contrary", 0x7E},
			{"Dark Aura", 0xBA},
			{"Drizzle", 0x2},
			{"Drought", 0x46},
			{"Dry Skin", 0x57},
			{"Fairy Aura", 0xBB},
			{"Flash Fire", 0x12},
			{"Forecast", 0x3B},
			{"Gale Wings", 0xB1},
			{"Hydration", 0x5D},
			{"Ice Body", 0x73},
			{"Illusion", 0x95},
			{"Imposter", 0x96},
			{"Infiltrator", 0x97},
			{"Intimidate", 0x16},
			{"Levitate", 0x1A},
			{"Magic Bounce", 0x9C},
			{"Mold Breaker", 0x68},
			{"Moody", 0x8D},
			{"Multitype", 0x79},
			{"No Guard", 0x63},
			{"Parental Bond", 0xB9},
			{"Pixilate", 0xB6},
			{"Poison Heal", 0x5A},
			{"Prankster", 0x9E},
			{"Pressure", 0x2E},
			{"Protean", 0xA8},
			{"Refrigerate", 0xAE},
			{"Regenerate", 0x90},
			{"Rough Skin", 0x18},
			{"Sand Force", 0x9F},
			{"Sand Stream", 0x2D},
			{"Scrappy", 0x71},
			{"Snow Warning", 0x75},
			{"Speed Boost", 0x3},
			{"Sturdy", 0x5},
			{"Telepathy", 0x8C},
			{"Teravolt", 0xA4},
			{"Trace", 0x24},
			{"Turbolaze", 0xA3},
			{"Unaware", 0x6D},
			{"Wonder Guard", 0x19}
		};
		
		std::vector<std::string> KBOptions;
		
		for (const KBSelection& KBName:KBArray)
			KBOptions.push_back(KBName.Name);
		
		Keyboard KB(entry->Name() + ":");
		KB.Populate(KBOptions, false);
		
		if (entry->IsActivated())
			KBValue = KBArray[KB.Open()].Value;
	}
	
	void SetAbility(MenuEntry *entry)
	{
		int& KBValue = *GetArg<int>(entry);
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			if (KBValue >= 0x2 && KBValue <= 0xBC)
			{
				for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
				{
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0x16, KBValue);
						WRITE16(g_Offset32 + 0x14E, KBValue);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0x16, KBValue);
						WRITE16(g_Offset32 + 0x14E, KBValue);
					}
				}
			}
		}
	}
	
	void GetCondition(MenuEntry *entry)
	{
		int& KBValue = *GetArg<int>(entry);
		
		const KBSelection KBArray[5] = 
		{
			{"Asleep", 0x24},
			{"Burned", 0x2C},
			{"Frozen", 0x28},
			{"Paralyzed", 0x20},
			{"Poisoned", 0x30}
		};
		
		std::vector<std::string> KBOptions;
		
		for (const KBSelection& KBName:KBArray)
			KBOptions.push_back(KBName.Name);
		
		Keyboard KB(entry->Name() + ":");
		KB.Populate(KBOptions, false);
		
		if (entry->IsActivated())
			KBValue = KBArray[KB.Open()].Value;
	}
	
	void SetCondition(MenuEntry *entry)
	{
		int& KBValue = *GetArg<int>(entry);
		
		if (IsInBattle() && entry->Hotkeys[0].IsPressed()) // Ensures that user is in battle and that the first hotkey is pressed
		{
			if (KBValue >= 0x24 && KBValue <= 0x30)
			{
				if (READ32(PartyPointer1[0], g_Data32) && g_Data32 != 0x0)
				{
					READ32(PartyPointer1[0], g_Offset32);
					
					for (int i = 0; i < 5; i++)
						WRITE8(g_Offset32 + (0x20 + (i * 4)), 0x0); // Resets any conditions (5) listed above to prevent overlapping
					
					READ32(PartyPointer2[0], g_Offset32);
					
					for (int i = 0; i < 5; i++)
						WRITE8(g_Offset32 + (0x20 + (i * 4)), 0x0); // Resets any conditions (5) listed above to prevent overlapping
				}
				
				for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
				{
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE8(g_Offset32 + KBValue, 0x1);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE8(g_Offset32 + KBValue, 0x1);
					}
				}
			}
		}
		
		else if (IsInBattle() && entry->Hotkeys[1].IsPressed()) // Ensures that user is in battle and that the second hotkey is pressed
		{
			if (READ32(PartyPointer1[0], g_Data32) && g_Data32 != 0x0) // Reads the first pointer of PartyPointer1 and if its data is not pointing to nothing
			{
				READ32(PartyPointer1[0], g_Offset32); // Reads the first pointer of PartyPointer1 and its offset
				
				for (int i = 0; i < 5; i++)
					WRITE8(g_Offset32 + (0x20 + (i * 4)), 0x0);
				
				READ32(PartyPointer2[0], g_Offset32); // Reads the first pointer of PartyPointer2 and its offset
				
				for (int i = 0; i < 5; i++)
					WRITE8(g_Offset32 + (0x20 + (i * 4)), 0x0);
			}
		}
	}
	
	void UnlimitedHP(MenuEntry *entry)
	{
		if (IsInBattle()) // Ensures that the user is in battle
		{
			for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
			{
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE16(g_Offset32 + 0xE, 0x3E7);
					WRITE16(g_Offset32 + 0x10, 0x3E7);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE16(g_Offset32 + 0xE, 0x3E7);
					WRITE16(g_Offset32 + 0x10, 0x3E7);
				}
			}
		}
	}
	
	void UnlimitedAP(MenuEntry *entry)
	{
		if (IsInBattle()) // Ensures that the user is in battle
		{
			for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
			{
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE16(g_Offset32 + 0x11E, 0x6363);
					WRITE16(g_Offset32 + 0x12C, 0x6363);
					WRITE16(g_Offset32 + 0x13A, 0x6363);
					WRITE16(g_Offset32 + 0x148, 0x6363);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE16(g_Offset32 + 0x11E, 0x6363);
					WRITE16(g_Offset32 + 0x12C, 0x6363);
					WRITE16(g_Offset32 + 0x13A, 0x6363);
					WRITE16(g_Offset32 + 0x148, 0x6363);
				}
			}
		}
	}
	
	void GetItemHeld(MenuEntry *entry)
	{
		int& KBValue = *GetArg<int>(entry);
		
		const KBSelection KBArray[67] = 
		{
			{"Adamant Orb", 0x87},
			{"Air Balloon", 0x21D},
			{"Assault Vest", 0x280},
			{"Black Belt", 0xF1},
			{"Black Sludge", 0x119},
			{"Blue Scarf", 0x105},
			{"Choice Band", 0xDC},
			{"Choice Scarf", 0x11F},
			{"Choice Specs", 0x129},
			{"Damp Rock", 0x11D},
			{"Destiny Ki", 0x118},
			{"Draco Plate", 0x137},
			{"Dread Plate", 0x138},
			{"Earth Plate", 0x131},
			{"Eject Button", 0x223},
			{"Expert Belt", 0x10C},
			{"Fist Plate", 0x12F},
			{"Flame Orb", 0x111},
			{"Flame Plate", 0x12A},
			{"Focus Band", 0xE6},
			{"Focus Sash", 0x113},
			{"Green Scarf", 0x107},
			{"Grip Claw", 0x11E},
			{"Griseous Orb", 0x70},
			{"Heat Rock", 0x11C},
			{"Icicle Plate", 0x11E},
			{"Icy Rock", 0x11A},
			{"Insect Plate", 0x134},
			{"Iron Plate", 0x139},
			{"King's Rock", 0xDD},
			{"Life Orb", 0x10E},
			{"Light Ball", 0xEC},
			{"Lustrous Orb", 0x88},
			{"Meadow Plate", 0x12D},
			{"Mental Herb", 0xDB},
			{"Metal Coat", 0xE9},
			{"Mind Plate", 0x133},
			{"Muscle Band", 0x10A},
			{"Never-Melt Ice", 0xF6},
			{"Pink Scarf", 0x106},
			{"Pixie Plate", 0x284},
			{"Power Anklet", 0x125},
			{"Power Band", 0x124},
			{"Power Belt", 0x122},
			{"Power Bracer", 0x121},
			{"Power Herb", 0x10F},
			{"Power Lens", 0x123},
			{"Power Weight", 0x126},
			{"Red Card", 0x21E},
			{"Red Scarf", 0x104},
			{"Rocky Helment", 0x21C},
			{"Sacred Ash", 0x2C},
			{"Sharp Beak", 0xF4},
			{"Silk Scarf", 0xFB},
			{"Sitrus Berry", 0x9E},
			{"Sky Plate", 0x132},
			{"Poke Ball", 0xE4},
			{"Smooth Rock", 0x11B},
			{"Soothe Bell", 0xDA},
			{"Soul Dew", 0xE1},
			{"Splash Plate", 0x12B},
			{"Spooky Plate", 0x136},
			{"Stone Plate", 0x135},
			{"Toxic Orb", 0x110},
			{"Toxic Plate", 0x130},
			{"Yellow Scarf", 0x108},
			{"Zap Plate", 0x12C}
		};
		
		std::vector<std::string> KBOptions;
		
		for (const KBSelection& KBName:KBArray)
			KBOptions.push_back(KBName.Name);
		
		Keyboard KB(entry->Name() + ":");
		KB.Populate(KBOptions, false);
		
		if (entry->IsActivated())
			KBValue = KBArray[KB.Open()].Value;
	}
	
	void SetItemHeld(MenuEntry *entry)
	{
		int& KBValue = *GetArg<int>(entry);
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			if (KBValue >= 0x2C && KBValue <= 0x284)
			{
				for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
				{
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0x12, KBValue);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0x12, KBValue);
					}
				}
			}
		}
	}
	
	void InterruptCharge(MenuEntry *entry)
	{
		if (IsInBattle()) // Ensures that the user is in battle
		{
			for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
			{
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0xCE, 0x1);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0xCE, 0x1);
				}
			}
		}
	}
	
	void InterruptRecharge(MenuEntry *entry)
	{
		if (IsInBattle()) // Ensures that the user is in battle
		{
			for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
			{
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0) // Reads the pointer and makes sure it's not pointing to nothing
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x16A, 0x0);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x16A, 0x0);
				}
			}
		}
	}
	
	void OneHitKO(MenuEntry *entry)
	{
		if (IsInBattle()) // Ensures that the user is in battle
		{
			if (READ32(EnemyPointer1[0], g_Data32) && g_Data32 != 0x0) // Reads the first pointer of PartyPointer1 and if its data is not pointing to nothing
			{
				READ32(EnemyPointer2[0], g_Offset32); // Reads the first pointer of PartyPointer2 and its offset
				
				if (READ16(g_Offset32 + 0x10, g_Data16) && g_Data16 > 0x1) // Checks if the actual HP is above 1 or not
				{
					// If HP is above 1, set current and max to 1
					READ32(EnemyPointer2[0], g_Offset32);
					WRITE16(g_Offset32 + 0xE, 0x1);
					WRITE16(g_Offset32 + 0x10, 0x1);
				}
				
				if (READ16(g_Offset32 + 0x10, g_Data16) && g_Data16 == 0x0) // Checks if the actual HP is equal to 0 or not
				{
					// If HP is equal to 0, set current and max to 0
					READ32(EnemyPointer1[0], g_Offset32);
					WRITE16(g_Offset32 + 0x10, 0x0);
					READ32(EnemyPointer2[0], g_Offset32);
					WRITE16(g_Offset32 + 0x10, 0x0);
				}
			}
		}
	}
	
	void GetExperience(MenuEntry *entry)
	{
		u8& KBValue = *GetArg<u8>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(3);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u8 Input = *static_cast<const u8 *>(In);
			
			if (Input >= 1 && Input <= 100)
				return (true);
			
			Error = "The value must be between 1-100.";
			return (false);
		});
		
		static u8 SavedValue;
		
		if (entry->IsActivated())
			KB.Open(KBValue, SavedValue);
		
		SavedValue = KBValue;
	}
	
	void SetExperience(MenuEntry *entry)
	{
		static u32 Address[2] =
		{
			0x579860,
			0x16B81C
		};
		
		u8& KBValue = *GetArg<u8>(entry);
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			if (KBValue >= 0x1)
			{
				WRITE32(Address[0], 0xE1D002B2);
				WRITE32(Address[0] + 0x04, 0xE92D4002);
				WRITE32(Address[0] + 0x08, 0xE3A01000 + KBValue);
				WRITE32(Address[0] + 0x0C, 0xE0000190);
				WRITE32(Address[0] + 0x10, 0xE8BD8002);
				WRITE32(Address[1], 0xEB10380F);
			}
		}
	}
	
	void AccessBag(MenuEntry *entry)
	{
		static u32 Pointer = 0x8000158;
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			if (entry->Hotkeys[0].IsDown())
			{
				if (READ32(Pointer, g_Data32) && g_Data32 != 0x0)
				{
					READ32(Pointer, g_Offset32);
					
					if (READ8(g_Offset32 + 0x77C, g_Data8) && g_Data8 == 0x3)
						WRITE8(g_Offset32 + 0x77C, 0x4);
				}
			}
		}
	}
	
	void OneHundredPercentShiny(MenuEntry *entry)
	{
		static u32 Address = 0x14ECA4;
		
		if (entry->IsActivated())
			WRITE32(Address, 0xEA00001C);
		
		if (!entry->IsActivated())
			WRITE32(Address, 0x0A00001C);
	}
	
	void OneHundredPercentCatch(MenuEntry *entry)
	{
		static u32 Pointer = 0x81FB510;
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			if (READ32(Pointer, g_Data32) && g_Data32 >= 0x8800000)
			{
				READ32(Pointer, g_Offset32);
				WRITE8(g_Offset32 + 0xB2, 0x1);
			}
		}
	}
	
	void InfiniteMegaEvolutions(MenuEntry *entry)
	{
		static u32 Pointer = 0x8000178;
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			if (READ32(Pointer, g_Data32) && g_Data32 != 0x0)
			{
				READ32(Pointer, g_Offset32);
				WRITE8(g_Offset32 + 0xEDD, 0x1);
			}
		}
	}
	
	struct Legendaries
	{
		const char *Name1;
		const char *Name2;
	};
	
	static const std::vector<Legendaries> LegendaryOptions =
	{
		{"#250", "#249"},
		{"#380", "#381"},
		{"#383", "#382"},
		{"#384", "#384"},
		{"#386", "#386"},
		{"#484", "#483"},
		{"#485", "#485"},
		{"#486", "#486"},
		{"#487", "#487"},
		{"#641", "#642"},
		{"#645", "#645"},
		{"#646", "#646"} 
	};
	
	void GetLegendaryRematch(MenuEntry *entry)
	{
		int& KBValue = *GetArg<int>(entry);
		
		static std::vector<std::string> KBOptions;
		
		if (KBOptions.empty())
		{
			for (const Legendaries &g : LegendaryOptions)
			{
				if (GameID == PkmnOR)
					KBOptions.push_back(g.Name1);
				
				if (GameID == PkmnAS)
					KBOptions.push_back(g.Name2);
			}
		}
		
		Keyboard KB(entry->Name() + ":", KBOptions);
		
		if (entry->IsActivated())
			KBValue = KB.Open();
	}
	
	void SetLegendaryRematch(MenuEntry *entry)
	{
		int& KBValue = *GetArg<int>(entry);
		
		if (KBValue == 0)
		{
			static u32 Address = 0x8C81DF2;
			
			if (READ16(Address, g_Data16) && (g_Data16 & ~0xFFF0) != 0x00)
			{
				READ8(Address, g_Data8);
				g_Data8 &= 0xF0;
				g_Data8 += 0x00;
				WRITE8(Address, g_Data8);
			}
		}
		
		if (KBValue == 1)
		{
			static u32 Address = 0x8C81E0C;
			
			if (READ16(Address, g_Data16) && (g_Data16 & ~0xFF0F) != 0x00)
			{
				READ8(Address, g_Data8);
				g_Data8 &= 0x0F;
				g_Data8 += 0x00;
				WRITE8(Address, g_Data8);
			}
		}
		
		if (KBValue == 2)
		{
			static u32 Address = AutoGame(0x8C81E29, 0x8C81E28);
			
			if (GameID == PkmnOR)
			{
				if (READ16(Address, g_Data16) && (g_Data16 & ~0xFFF0) != 0x00)
				{
					READ8(Address, g_Data8);
					g_Data8 &= 0xF0;
					g_Data8 += 0x00;
					WRITE8(Address, g_Data8);
				}
			}
			
			if (GameID == PkmnAS)
			{
				if (READ16(Address, g_Data16) && (g_Data16 & ~0xFF0F) != 0x00)
				{
					READ8(Address, g_Data8);
					g_Data8 &= 0x0F;
					g_Data8 += 0x00;
					WRITE8(Address, g_Data8);
				}
			}
		}
		
		if (KBValue == 3)
		{
			static u32 Address = 0x8C81E41;
			
			if (READ16(Address, g_Data16) && (g_Data16 & ~0xFF0F) != 0xE0)
			{
				READ8(Address, g_Data8);
				g_Data8 &= 0x0F;
				g_Data8 += 0xE0;
				WRITE8(Address, g_Data8);
			}
		}
		
		if (KBValue == 4)
		{
			static u32 Address = 0x8C81E4E;
			
			if (READ16(Address, g_Data16) && (g_Data16 & ~0xFFF0) != 0x00)
			{
				READ8(Address, g_Data8);
				g_Data8 &= 0xF0;
				g_Data8 += 0x00;
				WRITE8(Address, g_Data8);
			}
		}
		
		if (KBValue == 5)
		{
			static u32 Address = 0x8C81F38;
			
			if (READ16(Address, g_Data16) && (g_Data16 & ~0xFFF0) != 0x00)
			{
				READ8(Address, g_Data8);
				g_Data8 &= 0xF0;
				g_Data8 += 0x00;
				WRITE8(Address, g_Data8);
			}
		}
		
		if (KBValue == 6)
		{
			static u32 Address = 0x8C81DF8;
			
			if (READ16(Address, g_Data16) && (g_Data16 & ~0xFF0F) != 0x00)
			{
				READ8(Address, g_Data8);
				g_Data8 &= 0x0F;
				g_Data8 += 0x00;
				WRITE8(Address, g_Data8);
			}
		}
		
		if (KBValue == 7)
		{
			static u32 Address[2] =
			{
				0x8C81CC4,
				0x8C81DF7
			};
			
			if (READ16(Address[0], g_Data16) && (g_Data16 & ~0xFFF0) != 0x01)
			{
				READ8(Address[0], g_Data8);
				g_Data8 &= 0xF0;
				g_Data8 += 0x01;
				WRITE8(Address[0], g_Data8);
			}
			
			if (READ16(Address[1], g_Data16) && (g_Data16 & ~0xFF0F) != 0x00)
			{
				READ8(Address[1], g_Data8);
				g_Data8 &= 0x0F;
				g_Data8 += 0x00;
				WRITE8(Address[1], g_Data8);
			}
		}
		
		if (KBValue == 8)
		{
			static u32 Address = 0x8C81F38;
			
			if (READ16(Address, g_Data16) && (g_Data16 & ~0xFF0F) != 0x00)
			{
				READ8(Address, g_Data8);
				g_Data8 &= 0x0F;
				g_Data8 += 0x00;
				WRITE8(Address, g_Data8);
			}
		}
		
		if (KBValue == 9)
		{
			static u32 Address = 0x8C81F39;
			
			if (READ16(Address, g_Data16) && (g_Data16 & ~0xFF0F) != 0x00)
			{
				READ8(Address, g_Data8);
				g_Data8 &= 0x0F;
				g_Data8 += 0x00;
				WRITE8(Address, g_Data8);
			}
		}
		
		if (KBValue == 10)
		{
			static u32 Address = 0x8C81F3A;
			
			if (READ16(Address, g_Data16) && (g_Data16 & ~0xFFF0) != 0x00)
			{
				READ8(Address, g_Data8);
				g_Data8 &= 0xF0;
				g_Data8 += 0x00;
				WRITE8(Address, g_Data8);
			}
		}
		
		if (KBValue == 11)
		{
			static u32 Address = 0x8C81DEF;
			
			if (READ16(Address, g_Data16) && (g_Data16 & ~0xFFF0) != 0x00)
			{
				READ8(Address, g_Data8);
				g_Data8 &= 0xF0;
				g_Data8 += 0x00;
				WRITE8(Address, g_Data8);
			}
		}
	}
	
	void UnlockMegaEvolution(MenuEntry *entry)
	{
		static u32 Address = 0x8C8148A;
		
		if (READ16(Address, g_Data16) && (g_Data16 & ~0xFFF0) != 0x03)
		{
			READ8(Address, g_Data8);
			g_Data8 &= 0xF0;
			g_Data8 += 0x03;
			WRITE8(Address, g_Data8);
			MessageBox("You have finally unlocked the ability to Mega Evolve Pokemon during a battle!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		}
		
		else MessageBox("You have already unlocked the ability to Mega Evolve Pokemon during a battle!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
	}
}