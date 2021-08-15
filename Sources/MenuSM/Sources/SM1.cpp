#include <CTRPluginFramework.hpp>
#include "../../Helpers/Includes/Helpers.hpp"

using namespace CTRPluginFramework;

namespace SM
{
	u16 SpawnSpecies; u8 SpawnLevel, SpawnForm;
	
	static const std::vector<u32> PartyPointer1 = 
	{
		0x30000484, // Slot 1
		0x30000488, // Slot 2
		0x3000048C, // Slot 3
		0x30000490, // Slot 4
		0x30000494, // Slot 5
		0x30000498  // Slot 6
	};
	
	static const std::vector<u32> PartyPointer2 = 
	{
		0x3000746C, // Slot 1
		0x30007470, // Slot 2
		0x30007474, // Slot 3
		0x30007478, // Slot 4
		0x3000747C, // Slot 5
		0x30007480  // Slot 6
	};
	
	static const std::vector<u32> EnemyPointer1 = 
	{
		0x300004B4, // Slot 1
		0x300004B8, // Slot 2
		0x300004BC, // Slot 3
		0x300004C0, // Slot 4
		0x300004C4, // Slot 5
		0x300004C8  // Slot 6
	};
	
	static const std::vector<u32> EnemyPointer2 = 
	{
		0x3000749C, // Slot 1
		0x30007490, // Slot 2
		0x300074A4, // Slot 3
		0x300074A8, // Slot 4
		0x300074AC, // Slot 5
		0x300074A0  // Slot 6
	};
	
	static const std::vector<u32> EnemyHealthAddress =
	{
		0x30004DB6,
		0x30004DB8,
		0x3000BDA0
	};
	
	bool IsOnline = System::IsConnectedToInternet();
	
	bool IsInBattle(void) 
	{
		static u32 Pointer[2] =
		{
			0x30000158,
			0x30000180
		};
		
		// Reads the pointers and if its data is 0x40001 and 0x3, then is in battle. It also must be offline to return true
		if (READ32(Pointer[0], g_Data32) && g_Data32 == 0x40001 && READ8(Pointer[1], g_Data8) && g_Data8 == 0x3 && !IsOnline)
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
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0x1DA, KBValue);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0x1DA, KBValue);
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
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0x1DC, KBValue);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0x1DC, KBValue);
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
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0x1DE, KBValue);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0x1DE, KBValue);
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
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0x1E0, KBValue);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0x1E0, KBValue);
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
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0x1E2, KBValue);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0x1E2, KBValue);
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
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x1EA, 0x6 + KBValue);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x1EA, 0x6 + KBValue);
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
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x1EB, 0x6 + KBValue);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x1EB, 0x6 + KBValue);
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
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x1EC, 0x6 + KBValue);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x1EC, 0x6 + KBValue);
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
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x1ED, 0x6 + KBValue);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x1ED, 0x6 + KBValue);
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
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x1EE, 0x6 + KBValue);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x1EE, 0x6 + KBValue);
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
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x1EF, 0x6 + KBValue);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x1EF, 0x6 + KBValue);
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
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x1F0, 0x6 + KBValue);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x1F0, 0x6 + KBValue);
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
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE8(g_Offset32 + 0x1E4, KBValue);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE8(g_Offset32 + 0x1E4, KBValue);
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
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE8(g_Offset32 + 0x1E5, KBValue);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE8(g_Offset32 + 0x1E5, KBValue);
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
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
					{
						READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0x16, KBValue);
						WRITE16(g_Offset32 + 0x234, KBValue);
						READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
						WRITE16(g_Offset32 + 0x16, KBValue);
						WRITE16(g_Offset32 + 0x234, KBValue);
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
			{"Asleep", 0x30},
			{"Burned", 0x40},
			{"Frozen", 0x38},
			{"Paralyzed", 0x28},
			{"Poisoned", 0x48}
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
			if (KBValue >= 0x28 && KBValue <= 0x30)
			{
				if (READ32(PartyPointer1[0], g_Data32) && g_Data32 != 0x0)
				{
					READ32(PartyPointer1[0], g_Offset32);
					
					for (int i = 0; i < 5; i++)
						WRITE8(g_Offset32 + (0x24 + (i * 4)), 0x0); // Resets any conditions (5) listed above to prevent overlapping
					
					READ32(PartyPointer2[0], g_Offset32);
					
					for (int i = 0; i < 5; i++)
						WRITE8(g_Offset32 + (0x24 + (i * 4)), 0x0); // Resets any conditions (5) listed above to prevent overlapping
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
					WRITE8(g_Offset32 + (0x24 + (i * 4)), 0x0);
				
				READ32(PartyPointer2[0], g_Offset32); // Reads the first pointer of PartyPointer2 and its offset
				
				for (int i = 0; i < 5; i++)
					WRITE8(g_Offset32 + (0x24 + (i * 4)), 0x0);
			}
		}
	}
	
	void UnlimitedHP(MenuEntry *entry)
	{
		if (IsInBattle()) // Ensures that the user is in battle
		{
			for (int i = 0; i < 1; i++) // Only apply to the first slot, otherwise can go up to 6th slot
			{
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
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
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE16(g_Offset32 + 0x204, 0x6363);
					WRITE16(g_Offset32 + 0x212, 0x6363);
					WRITE16(g_Offset32 + 0x220, 0x6363);
					WRITE16(g_Offset32 + 0x22E, 0x6363);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE16(g_Offset32 + 0x204, 0x6363);
					WRITE16(g_Offset32 + 0x212, 0x6363);
					WRITE16(g_Offset32 + 0x220, 0x6363);
					WRITE16(g_Offset32 + 0x22E, 0x6363);
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
					if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
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
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x18B, 0x1);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x18B, 0x1);
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
				if (READ32(PartyPointer1[i], g_Data32) && g_Data32 != 0x0)
				{
					READ32(PartyPointer1[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x254, 0x0);
					READ32(PartyPointer2[i], g_Offset32); // Reads the pointer and its offset
					WRITE8(g_Offset32 + 0x254, 0x0);
				}
			}
		}
	}
	
	void OneHitKO(MenuEntry *entry)
	{
		static const u32 Address[3] =
		{
			0x30004DB6,
			0x30004DB8,
			0x3000BDA0
		};
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			for (int i = 0; i < 6; i++)
			{
				// If Actual HP is above 1, set it to 1
				if (READU16(Address[2] + (i * 0x330)) > 0x1)
				{
					WRITEU16(Address[1] + (i * 0x330), READU16(Address[0] + (i * 0x330)));
					WRITEU16(Address[2] + (i * 0x330), 0x1);
				}
				
				// If actual HP is 0, make displayed HP match
				else if (READU16(Address[2] + (i * 0x330)) == 0x0)
					WRITEU16(Address[1] + (i * 0x330), 0x0);
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
			0x595800,
			0x48F1EC
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
				WRITE32(Address[1], 0xEB041983);
			}
		}
	}
	
	void AccessBag(MenuEntry *entry)
	{
		static u32 Pointer = 0x302E05B4;
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			if (entry->Hotkeys[0].IsDown())
			{
				if (READ32(Pointer, g_Data32) && g_Data32 != 0x0)
				{
					READ32(Pointer, g_Offset32);
					
					if (READ8(g_Offset32 + 0x760, g_Data8) && g_Data8 == 0x1)
						WRITE8(g_Offset32 + 0x760, 0x3);
				}
			}
		}
	}
	
	void OneHundredPercentShiny(MenuEntry *entry)
	{
		static u32 Address = 0x318AF0;
		
		if (entry->IsActivated())
			WRITE32(Address, 0xEA00001C);
		
		if (!entry->IsActivated())
			WRITE32(Address, 0x0A00001C);
	}
	
	void OneHundredPercentCatch(MenuEntry *entry)
	{
		static u32 Address[2] =
		{
			0x59775C,
			0x490E68
		};
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			WRITE32(Address[0], 0xE5D00008);
			WRITE32(Address[0] + 0x04, 0xE92D4003);
			WRITE32(Address[0] + 0x08, 0xE59D0010);
			WRITE32(Address[0] + 0x0C, 0xE59F100C);
			WRITE32(Address[0] + 0x10, 0xE1510000);
			WRITE32(Address[0] + 0x14, 0x024000F8);
			WRITE32(Address[0] + 0x18, 0x058D0010);
			WRITE32(Address[0] + 0x1C, 0xE8BD8003);
			WRITE32(Address[0] + 0x20, 0x006DA1CC);
			WRITE32(Address[1], 0xEB041A3B);
		}
	}
	
	void TrainerRematch(MenuEntry *entry)
	{
		static u32 Address = 0x49EFC8;
		
		if (entry->IsActivated())
		{
			WRITE32(Address, 0xE3A00000);
			WRITE32(Address + 0x4, 0xE12FFF1E);
		}
		
		if (!entry->IsActivated())
		{
			WRITE32(Address, 0xE5911004);
			WRITE32(Address + 0x4, 0xE5900044);
		}
	}
	
    void ZMovesWithoutCrystal(MenuEntry *entry)
    {
		static u32 Address[3] =
		{
			0x597800,
			0x314300,
			0x36DFF4
		};
		
		static u32 Data[11] = 
		{
			0xE92D4005, 0xE1A00006, 0xEA000000, 0xE92D4005,
			0xE59D2050, 0xE59F100C, 0xE1510002, 0x01D510B4,
			0x11A01000, 0xE8BD8005, 0x0078BF60
		};
		
		if (entry->WasJustActivated())
		{
			if (!Process::Patch(Address[0], Data, 0x2C))
				goto Error;
		}
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			if (entry->Hotkeys[0].IsDown())
			{
				if (!WRITE32(Address[1], 0xEB0A0D3E))
					goto Error;
				
				if (!WRITE32(Address[1] + 0x70, 0xEB0A0D25))
					goto Error;
				
				if (!WRITE32(Address[2], 0xE3A00001))
					goto Error;
			}
			
			else
			{
				if (!WRITE32(Address[2], 0xE3A00000))
					goto Error;
			}
		}
		
		if (!entry->IsActivated())
		{
			if (!WRITE32(Address[1], 0xE1D510B4))
				goto Error;
			
			if (!WRITE32(Address[1] + 0x70, 0xE1D510B4))
				goto Error;
			
			if (!WRITE32(Address[2], 0xE3A00000))
				goto Error;
		}
		
		Error: return;
    }
	
    void MegaEvolveWithoutStone(MenuEntry *entry)
    {
		static u32 Address[2] =
		{
			0x5976E0,
			0x491AFC
		};
		
		static u32 Data[34] = 
		{
			0xE1A05001, 0xE92D403E, 0xE59F1064, 0xE59D2044,
			0xE1510002, 0x03A00000, 0x059D2014, 0x028220E4,
			0x058D2014, 0x08BD803E, 0xE59D2034, 0xE59F1044,
			0xE1510002, 0x0A000002, 0xE59F103C, 0xE1510002,
			0x18BD803E, 0xE59D1038, 0xE59F2030, 0xE59F3030,
			0xE2834018, 0xE4925004, 0xE4936004, 0xE1510005,
			0x11510006, 0x0AFFFFEA, 0xE1530004, 0x1AFFFFF8,
			0xE8BD803E, 0x0077C234, 0x00324140, 0x00324160,
			0x30000404, 0x300073EC,
		};
		
		static u32 Jump[1] = {0xEB0416F7};
		static u32 Original[1] = {0x0};
		
		if (entry->WasJustActivated())
		{
			if (!Process::Patch(Address[0], Data, 0x88)) 
				goto Error;
			
			if (!Process::Patch(Address[1], Jump, 0x4, Original)) 
				goto Error;
		}
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			if (entry->Hotkeys[0].IsPressed())
			{
				if (!WRITE8(Address[0] + 0x14, 0x2))
					goto Error;
			}
			
			else
			{
				if (!WRITE8(Address[0] + 0x14, 0x1))
					goto Error;
			}
		} 
		
		if (!entry->IsActivated())
		{
			if (!Process::Patch(Address[1], Original, 0x4))
				goto Error;
		}
		
		Error: return;
    }
	
	void CatchTrainerPokemon(MenuEntry *entry)
	{
		static u32 Address[2] =
		{
			0x597780,
			0x2FEA2C
		};
		
		if (IsInBattle()) // Ensures that the user is in battle
		{
			WRITE32(Address[0], 0xE1A03002);
			WRITE32(Address[0] + 0x04, 0xE92D4003);
			WRITE32(Address[0] + 0x08, 0xE59D000C);
			WRITE32(Address[0] + 0x0C, 0xE59F1014);
			WRITE32(Address[0] + 0x10, 0xE1510000);
			WRITE32(Address[0] + 0x14, 0x05940004);
			WRITE32(Address[0] + 0x18, 0x0590000C);
			WRITE32(Address[0] + 0x1C, 0x03A01000);
			WRITE32(Address[0] + 0x20, 0x05C01000);
			WRITE32(Address[0] + 0x24, 0xE8BD8003);
			WRITE32(Address[0] + 0x28, 0x006D42AC);
			
			if (entry->IsActivated())
				WRITE32(Address[1], 0xEB0A6353);
			
			if (!entry->IsActivated())
				WRITE32(Address[1], 0xE1A03002);
		}
	}
	
	std::vector<std::string> ListOfForms(int SpawnSpecies)
	{
		std::vector<std::string> Options;
		
		switch (SpawnSpecies) 
		{
			case 3:   // Venusaur
			case 9:   // Blastoise
			case 15:  // Beedrill
			case 18:  // Pidgeot
			case 65:  // Alakazam
			case 80:  // Slowbro
			case 94:  // Gengar
			case 115: // Kangaskhan
			case 127: // Pinsir
			case 130: // Gyarados
			case 142: // Aerodactyl
			case 181: // Ampharos
			case 208: // Steelix
			case 212: // Scizor
			case 214: // Heracross
			case 229: // Houndoom
			case 248: // Tyranitar
			case 254: // Sceptile
			case 257: // Blaziken
			case 260: // Swampert
			case 282: // Gardevoir
			case 302: // Sableye
			case 303: // Mawile
			case 306: // Aggron
			case 308: // Medicham
			case 310: // Manectric
			case 319: // Sharpedo
			case 323: // Camerupt
			case 334: // Altaria
			case 354: // Banette
			case 359: // Absol
			case 362: // Glalie
			case 373: // Salamence
			case 376: // Metagross
			case 380: // Latias
			case 381: // Latios
			case 384: // Rayquaza
			case 428: // Lopunny
			case 445: // Garchomp
			case 448: // Lucario
			case 460: // Abomasnow
			case 475: // Gallade
			case 531: // Audino
			case 719: // Diancie
				Options = {"Normal", "Mega"};
				break;
			
			case 6:   // Charizard
			case 150: // Mewtwo
				Options = {"Normal", "Mega X", "Mega Y"};
				break;
			
			case 19:  // Rattata
			case 26:  // Raichu
			case 27:  // Sandshrew
			case 28:  // Sandslash
			case 37:  // Vulpix
			case 38:  // Ninetails
			case 50:  // Diglett
			case 51:  // Dugtrio
			case 52:  // Meowth
			case 53:  // Persian
			case 74:  // Geodude
			case 75:  // Graveler
			case 76:  // Golem
			case 88:  // Grimer
			case 89:  // Muk
			case 105: // Exeggutor
				Options = {"Normal", "Alola"};
				break;
			
			case 20:  // Raticate
			case 103: // Marowak
				Options = {"Normal", "Alola", "Totem"};
				break;
			
			case 25:  // Pikachu
				Options = {"Normal", "Original Cap", "Hoenn Cap", "Sinnoh Cap", "Unova Cap", "Kalos Cap", "Alola Cap", "Partner Cap"};
				break;
			
			case 201: // Unown
				Options = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "!", "?"};
				break;
			
			case 351: // Castform
				Options = {"Normal", "Sunny", "Rainy", "Snowy"};
				break;
			
			case 382: // Kyogre
			case 383: // Groudon
				Options = {"Normal", "Primal"};
				break;
			
			case 386: //Deoxys
				Options = {"Normal", "Attack", "Defense", "Speed"};
				break;
			
			case 412: // Burmy
			case 413: // Wormadam
			case 414: // Mothim
				Options = {"Plant", "Sandy", "Trash"};
				break;
			
			case 422: // Shellos
			case 423: //Gastrodon
				Options = {"East", "West"};
				break;
			
			case 479: // Rotom
				Options = {"Normal", "Heat", "Wash", "Frost", "Fan", "Mow"}; 
				break;
			
			case 487: // Giratina
				Options = {"Altered", "Origin"};
				break;
			
			case 492: // Shaymin
				Options = {"Land", "Sky"};
				break;
			
			case 493: // Arceus
			case 773: // Silvally
				Options = {"Normal", "Fighting", "Flying", "Poison", "Ground", "Rock", "Bug", "Ghost", "Steel", "Fire", "Water", "Grass", "Electric", "Psychic", "Ice", "Dragon", "Dark", "Fairy"}; 
				break;
			
			case 550: // Basculin
				Options = {"Red", "Blue"};
				break;
			
			case 555: // Darmanitan
				Options = {"Standard", "Zen"};
				break;
			
			case 585: // Deerling
			case 586: // Sawsbuck
				Options = {"Spring", "Summer", "Autumn", "Winter"};
				break;
			
			case 641: // Tornadus
			case 642: // Thundurus
			case 645: // Landorus
				Options = {"Incarnate", "Therian"};
				break;
			
			case 646: // Kyurem
				Options = {"Normal", "White", "Black"};
				break;
			
			case 647: //Keldeo
				Options = {"Ordinary", "Resolute"};
				break;
			
			case 648: // Meloetta
				Options = {"Aria", "Pirouette"};
				break;
			
			case 649: // Genesect
				Options = {"Normal", "Douse", "Shock", "Burn", "Chill"};
				break;
				
			case 658: //Greninja
				Options = {"Normal", "Ash", "Bonded"};
				break;
			
			case 664: // Scatterbug
			case 665: // Spewpa
			case 666: // Vivillon
				Options = {"Icy Snow", "Polar", "Tundra", "Continental", "Garden", "Elegant", "Meadow", "Modern", "Marine", "Archipelago", "High-Plains", "Sandstorm", "River", "Monsoon", "Savannah", "Sun", "Ocean", "Jungle", "Fancy", "Poke Ball"}; 
				break;
			
			case 669: // Flabébé
			case 671: // Florges
				Options = {"Red", "Yellow", "Orange", "Blue", "White"};
				break;
			
			case 670: // Floette
				Options = {"Red", "Yellow", "Orange", "Blue", "White", "Eternal"};
				break;
			
			case 676: //Furfrou
				Options = {"Natural", "Heart", "Star", "Diamond", "Deputante", "Matron", "Dandy", "La Reine", "Kabuki", "Pharaoh"};
				break;
			
			case 681: // Aegislash
				Options = {"Shield", "Blade"};
				break;
			
			case 710: // Pumpkaboo
			case 711: // Gourgeist
				Options = {"Average", "Small", "Large", "Super"};
				break;
			
			case 716: // Xerneas
				Options = {"Neutral", "Active"};
				break;
			
			case 718: // Zygarde
				Options = {"50%", "10%", "10%-C", "50%-C", "100%-C"}; 
				break;
			
			case 720: // Hoopa
				Options = {"Confined", "Unbound"};
				break;
			
			case 735: // Gumshoos
			case 738: // Vikavolt
			case 743: // Ribombee
			case 752: // Araquanid
			case 754: // Lurantis
			case 758: // Salazzle
			case 777: // Togedemaru
			case 784: // Kommo-o
				Options = {"Normal", "Totem"};
				break;
			
			case 741: // Oricorio
				Options = {"Red", "Yellow", "Pink", "Blue"};
				break;
			
			case 745: // Lycanroc
				Options = {"Midday", "Midnight", "Dusk"};
				break;
			
			case 746: // Wishiwashi
				Options = {"Normal", "School"};
				break;
			
			case 774: // Minior
				Options = {"Random"};
				break;
			
			case 778: // Mimikyu
				Options = {"Disguised", "Busted", "Totem-Disquised", "Totem-Busted"};
				break;
			
			case 801: // Magearna
				Options = {"Normal", "Original"};
				break;
			
			default:  // All Others
				Options = {"Normal"};
				break;
		}
		
		return Options;
	}
	
	void GetPokemonSpawner(MenuEntry *entry)
	{
		if (entry->IsActivated())
		{
			Keyboard KB1("Species:");
			KB1.IsHexadecimal(false);
			KB1.SetMaxLength(3);
			KB1.SetCompareCallback([](const void *In, std::string &Error)
			{
				u16 Input = *static_cast<const u16 *>(In);
				
				if (Input >= 1 && Input <= 802)
					return (true);
				
				Error = "The value must be between 1-802.";
				return (false);
			});
			
			static u16 SavedValue1;
			KB1.Open(SpawnSpecies, SavedValue1);
			SavedValue1 = SpawnSpecies;
			
			if (!Controller::IsKeyPressed(Key::B))
			{
				Keyboard KB2("Level:");
				KB2.IsHexadecimal(false);
				KB2.SetMaxLength(3);
				KB2.SetCompareCallback([](const void *In, std::string &Error)
				{
					u8 Input = *static_cast<const u8 *>(In);
					
					if (Input >= 1 && Input <= 100)
						return (true);
					
					Error = "The value must be between 1-100.";
					return (false);
				});
				
				static u8 SavedValue2;
				KB2.Open(SpawnLevel, SavedValue2);
				SavedValue2 = SpawnLevel;
				
				if (!Controller::IsKeyPressed(Key::B))
				{
					int Userchoice;
					Keyboard KB3("Form:");
					KB3.Populate(ListOfForms(SpawnSpecies));
					Userchoice = KB3.Open();
					
					if (Userchoice != -1)
						SpawnForm = Userchoice;
				}
			}
			
			if (Controller::IsKeyPressed(Key::B))
			{
				entry->Disable();
				return;
			}
		}
	}
	
	void SetPokemonSpawner(MenuEntry *entry)
	{
		static u32 Address[4] =
		{
			0x597BA0,
			0x399CB4,
			0x399C9C,
			0x399D50
		};
		
		static u32 Data[10] =
		{
			0xE92D400E, 0xE59F0014, 0xE3500000, 0x18BD800E, 
			0xE59F000C, 0xEBF83F51, 0xE2800001, 0xE8BD800E, 
			0x00000000, 0x00000327,
		};
		
		static u32 Jump[2] = 
		{
			0xEB07F7B9,
			0xE1D400B0
		};
		
		static u32 Original[1] = {0x0};
		
		if (entry->WasJustActivated())
		{
			if (!Process::Patch(Address[0], Data, 0x28))
				goto Error;
			
			if (!WRITE32(Address[1] + 0x00, Jump[0]))
				goto Error;
			
			if (!WRITE32(Address[1] + 0x10, Jump[1]))
				goto Error;
			
			if (!WRITE32(Address[1] + 0x2C, Jump[1]))
				goto Error;
			
			if (!Process::Patch(Address[2], (void *) (0xE3A00000), 0x4, Original))
				goto Error;
			
			if (!Process::Patch(Address[3], (void *) (0xC3A00000), 0x4, Original))
				goto Error;
		}
		
		if (entry->IsActivated())
		{
			if (!WRITE32(Address[0] + 0x20, SpawnSpecies))
				goto Error;
			
			if (!WRITE32(Address[2], 0xE3A00000 + SpawnLevel))
				goto Error;
			
			if (!WRITE32(Address[3], 0xC3A00000 + SpawnForm))
				goto Error;
		}
		
		else if (!entry->IsActivated())
		{
			if (!WRITE32(Address[1] + 0x00, 0xE1D500B0))
				goto Error;
			
			if (!WRITE32(Address[1] + 0x10, 0xE1D500B0))
				goto Error;
			
			if (!WRITE32(Address[1] + 0x2C, 0xE1D500B0))
				goto Error;
			
			if (!Process::Patch(Address[2], Original, 0x4))
				goto Error;
			
			if (!Process::Patch(Address[3], Original, 0x4))
				goto Error;
		}
		
		Error: return;
	}
}