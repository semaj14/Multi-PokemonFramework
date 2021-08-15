#include <CTRPluginFramework.hpp>
#include "../../Helpers/Includes/Helpers.hpp"

using namespace CTRPluginFramework;

namespace XY
{
	int Direction; float CoordinateX, CoordinateY;
	
	static const u8 OPowers[] =
	{
		0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x0A, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00
	};
	
	void GetWarper(MenuEntry *entry)
	{
		int& KBValue = *GetArg<int>(entry);
		
		const KBSelection KBArray[28] = 
		{
			{"Ambrette Town", 0x2F},
			{"Anistar City", 0xD6},
			{"Battle Maison", 0xF2},
			{"Camphrier Town", 0xD},
			{"Coumarine City", 0xBE},
			{"Couriway Town", 0x28},
			{"Cyllage City", 0x9F},
			{"Day Care", 0x109},
			{"Dendemille Town", 0x21},
			{"Friend Safari", 0x163},
			{"Geosenge Town", 0x18},
			{"Kiloude City", 0xEA},
			{"Laverre City", 0xCA},
			{"Lumiose City", 0x167},
			{"Poké Ball Factory", 0x136},
			{"Pokémon Lab", 0x53},
			{"Pokémon League", 0xF4},
			{"Radiant Chamber", 0x100},
			{"Santalune City", 0x36},
			{"Santalune Forest", 0x11E},
			{"Sea Spirit's Den", 0x15F},
			{"Shalour City", 0xAE},
			{"Snowbelle City", 0xE1},
			{"Team Flare HQ", 0x155},
			{"Terminus Cave", 0x15A},
			{"Unknown Dungeon", 0x13F},
			{"Vanville Town", 0x2},
			{"Video Studio", 0x6B}
		};
		
		std::vector<std::string> KBOptions;
		
		for (const KBSelection& KBName:KBArray)
			KBOptions.push_back(KBName.Name);
		
		Keyboard KB(entry->Name() + ":");
		KB.CanAbort(false);
		KB.Populate(KBOptions, false);
		
		if (entry->IsActivated())
			KBValue = KBArray[KB.Open()].Value;
		
		switch (KBValue)
		{
			case 0xF2:
				Direction = 0;
				CoordinateX = 369;
				CoordinateY = 567;
				break;
			
			case 0x109:
				Direction = 0;
				CoordinateX = 225;
				CoordinateY = 351;
				break;
			
			case 0x163:
				Direction = 0;
				CoordinateX = 153;
				CoordinateY = 315;
				break;
			
			case 0x136:
				Direction = 0;
				CoordinateX = 279;
				CoordinateY = 621;
				break;
			
			case 0x53:
				Direction = 0;
				CoordinateX = 207;
				CoordinateY = 261;
				break;
			
			case 0x100:
				Direction = 0;
				CoordinateX = 351;
				CoordinateY = 423;
				break;
			
			case 0x11E:
				Direction = 0;
				CoordinateX = 729;
				CoordinateY = 1359;
				break;
			
			case 0x15F:
				Direction = 0;
				CoordinateX = 333;
				CoordinateY = 405;
				break;
			
			case 0x155:
				Direction = 0;
				CoordinateX = 711;
				CoordinateY = 891;
				break;
			
			case 0x15A:
				Direction = 0;
				CoordinateX = 765;
				CoordinateY = 693;
				break;
			
			case 0x13F:
				Direction = 0;
				CoordinateX = 351;
				CoordinateY = 567;
				break;
			
			case 0x6B:
				Direction = 0;
				CoordinateX = 315;
				CoordinateY = 585;
				break;
			
			default:
				Direction = 0;
				CoordinateX = 369;
				CoordinateY = 495;
				break;
		}
	}
	
	void SetWarper(MenuEntry *entry)
	{
		static u32 Address[3] =
		{
			0x8803BCA,
			0x8C67192,
			0x8C671A0
		};
		
		int& KBValue = *GetArg<int>(entry);
		
		if (entry->Hotkeys[0].IsDown() && KBValue != 0x0)
		{
			WRITE16(Address[0], KBValue);
			
			// Set the proper direction the player is supposed to face
			WRITE8(Address[1], Direction);
			
			// Set the proper coordinates depending on the location
			WRITEFLOAT(Address[2], CoordinateX);
			WRITEFLOAT(Address[2] + 0x8, CoordinateY);
		}
	}
	
	void WalkThroughWalls(MenuEntry *entry)
	{
		static u32 Address[3] =
		{
			0x053ED50,
			0x80B5820,
			0x80B3A1C
		};
		
		WRITE32(Address[0], 0xE1A01000);
		WRITE32(Address[0] + 0x4, 0xE12FFF1E);
		WRITE32(Address[0] + 0x8, 0xE1A06000);
		WRITE32(Address[0] + 0xC, 0xE12FFF1E);
		
		if (Controller::GetKeysDown() || Controller::GetKeysReleased())
		{
			WRITE32(Address[0], 0xE3A01000);
			WRITE32(Address[0] + 0x8, 0xE3A06000);
		}
		
		if (READ32(Address[1], g_Data32) && g_Data32 == 0xE1A01000)
			WRITE32(Address[1], 0xEBF8914A);
		
		if (READ32(Address[2], g_Data32) && g_Data32 == 0xE1A06000)
			WRITE32(Address[2], 0xEBF898CD);
	}
	
	void FlyAnywhere(MenuEntry *entry)
	{
		static u32 Address[2] =
		{
			0x8C61CF0,
			0x8C7A81C
		};
		
		if (READ32(Address[0], g_Data32) && g_Data32 == 0x6B65C4)
		{
			WRITE32(Address[0], 0x6B6A30);
			
			if (READ16(Address[1], g_Data16) && (g_Data16 & ~0xFF00) != 0xF7)
			{
				READ8(Address[1], g_Data8);
				g_Data8 &= 0x00;
				g_Data8 += 0xF7;
				WRITE8(Address[1], g_Data8);
			}
			
			if (READ16(Address[1] + 0x1, g_Data16) && (g_Data16 & ~0xFF00) != 0xFF)
			{
				READ8(Address[1] + 0x1, g_Data8);
				g_Data8 &= 0x00;
				g_Data8 += 0xFF;
				WRITE8(Address[1] + 0x1, g_Data8);
			}
			
			if (READ16(Address[1] + 0x2, g_Data16) && (g_Data16 & ~0xFFF0) != 0x0F)
			{
				READ8(Address[1] + 0x2, g_Data8);
				g_Data8 &= 0xF0;
				g_Data8 += 0x0F;
				WRITE8(Address[1] + 0x2, g_Data8);
			}
		}
	}
	
	void RepelLastsForever(MenuEntry *entry)
	{
		static u32 Address = 0x436AE4;
		
		if (entry->IsActivated())
			WRITE32(Address, 0xE320F000);
		
		if (!entry->IsActivated())
			WRITE32(Address, 0xE2411001);
	}
	
	void GetOPower(MenuEntry *entry)
	{
		u8& KBValue = *GetArg<u8>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(2);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			u8 Input = *static_cast<const u8 *>(In);
			
			if (Input >= 0 && Input <= 10)
				return (true);
			
			Error = "The value must be between 0-10.";
			return (false);
		});
		
		static u8 SavedValue;
		
		if (entry->IsActivated())
			KB.Open(KBValue, SavedValue);
		
		SavedValue = KBValue;
	}
	
	void SetOPower(MenuEntry *entry)
	{
		static u32 Address[3] =
		{
			0x8C7BB00,
			0x8C7BB64,
			0x0114620
		};
		
		u8& KBValue = *GetArg<u8>(entry);
		WRITE8(Address[1], KBValue);
		
		if (entry->IsActivated())
			WRITE32(Address[2], 0xE12FFF1E);
		
		if (!entry->IsActivated())
			WRITE32(Address[2], 0xE92D4070);
		
		if (entry->Hotkeys[0].IsDown())
			Process::CopyMemory((void *)(Address[0]), OPowers, 0x48);
	}
	
	void NoOutlines(MenuEntry *entry)
	{
		static u32 Address = 0x362ED8;
		
		if (entry->IsActivated())
		{
			WRITE32(Address, 0x0);
			WRITE32(Address + 0x4, 0x0);
		}
		
		if (!entry->IsActivated())
		{
			WRITE32(Address, 0xBF800000);
			WRITE32(Address + 0x4, 0x3F800000);
		}
	}
	
	void InstantDialogs(MenuEntry *entry)
	{
		static u32 Address[2] =
		{
			0x3F6FB4,
			0x3F7818
		};
		
		if (entry->IsActivated())
		{
			WRITE32(Address[0], 0xE3A04003);
			WRITE32(Address[1], 0xE3A05003);
		}
		
		if (!entry->IsActivated())
		{
			WRITE32(Address[0], 0xE1A04001);
			WRITE32(Address[1], 0xE5D05000);
		}
	}
}