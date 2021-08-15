#include <CTRPluginFramework.hpp>

#include "../../Helpers/KeyboardHelpers.hpp"
#include "../../Helpers.hpp"

using namespace CTRPluginFramework;

namespace ORAS
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
		
		const KBSelection KBArray[37] = 
		{
			{"Ancient Tomb", 0x9F},
			{"Battle Resort", 0x206},
			{"Cave of Origin", 0x70},
			{"Day Care", 0x187},
			{"Desert Ruins", 0x4D},
			{"Dewford Town", 0xE8},
			{"Ever Grande City", 0x161},
			{"Fabled Cave", 0x20F},
			{"Fallarbor Town", 0xF0},
			{"Fortree City", 0x12D},
			{"Gnarled Den", 0x210},
			{"Granite Cave", 0x4E},
			{"Island Cave", 0x9E},
			{"Lilycove City", 0x135},
			{"Littleroot Town", 0xDF},
			{"Mauville City", 0x116},
			{"Meteor Falls", 0x47},
			{"Mossdeep City", 0x14A},
			{"Nameless Cavern", 0x20E},
			{"New Mauville", 0x8B},
			{"Odale Town", 0xE4},
			{"Pacifidlog Town", 0xFD},
			{"Petalburg City", 0x103},
			{"Petalburg Woods", 0x52},
			{"Pokémon League", 0x16C},
			{"Rustboro City", 0x11C},
			{"Rusturf Tunnel", 0x4B},
			{"Scorched Slab", 0xA7},
			{"Sea Mauville", 0x92},
			{"Sealed Chambers", 0xA3},
			{"Secret Meadow", 0x1DB},
			{"Shoal Cave", 0x84},
			{"Sky Pillar", 0xB0},
			{"Slateport City", 0x109},
			{"Sootopolis City", 0x155},
			{"Verdanturf Town", 0xF6},
			{"Victory Road", 0x7B}
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
			case 0x9F:
				Direction = 0;
				CoordinateX = 225;
				CoordinateY = 333;
				break;
			
			case 0x70:
				Direction = 0;
				CoordinateX = 333;
				CoordinateY = 621;
				break;
			
			case 0x187:
				Direction = 0;
				CoordinateX = 225;
				CoordinateY = 333;
				break;
			
			case 0x4D:
				Direction = 0;
				CoordinateX = 225;
				CoordinateY = 333;
				break;
			
			case 0x20F:
				Direction = 0;
				CoordinateX = 387;
				CoordinateY = 693;
				break;
			
			case 0x210:
				Direction = 0;
				CoordinateX = 369;
				CoordinateY = 657;
				break;
			
			case 0x4E:
				Direction = 0;
				CoordinateX = 531;
				CoordinateY = 639;
				break;
			
			case 0x9E:
				Direction = 0;
				CoordinateX = 225;
				CoordinateY = 333;
				break;
			
			case 0xDF:
				Direction = 0;
				CoordinateX = 297;
				CoordinateY = 333;
				break;
			
			case 0x47:
				Direction = 0;
				CoordinateX = 1035;
				CoordinateY = 639;
				break;
			
			case 0x20E:
				Direction = 0;
				CoordinateX = 369;
				CoordinateY = 657;
				break;
			
			case 0x8B:
				Direction = 0;
				CoordinateX = 369;
				CoordinateY = 693;
				break;
			
			case 0x52:
				Direction = 0;
				CoordinateX = 531;
				CoordinateY = 1161;
				break;
			
			case 0x16C:
				Direction = 0;
				CoordinateX = 297;
				CoordinateY = 387;
				break;
			
			case 0x4B:
				Direction = 0;
				CoordinateX = 261;
				CoordinateY = 369;
				break;
			
			case 0xA7:
				Direction = 0;
				CoordinateX = 261;
				CoordinateY = 459;
				break;
			
			case 0x92:
				Direction = 1;
				CoordinateX = 369;
				CoordinateY = 45;
				break;
			
			case 0xA3:
				Direction = 0;
				CoordinateX = 801;
				CoordinateY = 1305;
				break;
			
			case 0x1DB:
				Direction = 0;
				CoordinateX = 387;
				CoordinateY = 657;
				break;
			
			case 0x84:
				Direction = 0;
				CoordinateX = 387;
				CoordinateY = 639;
				break;
			
			case 0xB0:
				Direction = 0;
				CoordinateX = 729;
				CoordinateY = 981;
				break;
			
			case 0x7B:
				Direction = 0;
				CoordinateX = 387;
				CoordinateY = 855;
				break;
			
			default:
			{
				Direction = 0;
				CoordinateX = 351;
				CoordinateY = 441;
			}
			break;
		}
	}
	
	void SetWarper(MenuEntry *entry)
	{
		static u32 Address[3] =
		{
			0x8803BCA,
			0x8C6E886,
			0x8C6E894
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
			0x0579820,
			0x80BB414,
			0x80B87F8
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
			WRITE32(Address[1], 0xEBF83D01);
		
		if (READ32(Address[2], g_Data32) && g_Data32 == 0xE1A06000)
			WRITE32(Address[2], 0xEBF8480A);
	}
	
	void FlyAnywhere(MenuEntry *entry)
	{
		static u32 Address[2] =
		{
			0x8C69330,
			0x8C81F24
		};
		
		if (READ32(Address[0], g_Data32) && g_Data32 == 0x7007C0)
		{
			WRITE32(Address[0], 0x700C38);
			
			if (READ16(Address[1], g_Data16) && (g_Data16 & ~0xFF0F) != 0xC0)
			{
				READ8(Address[1], g_Data8);
				g_Data8 &= 0x0F;
				g_Data8 += 0xC0;
				WRITE8(Address[1], g_Data8);
			}
			
			if (READ16(Address[1] + 0x1, g_Data16) && (g_Data16 & ~0xFF00) != 0xFF)
			{
				READ8(Address[1] + 0x1, g_Data8);
				g_Data8 &= 0x00;
				g_Data8 += 0xFF;
				WRITE8(Address[1] + 0x1, g_Data8);
			}
			
			if (READ16(Address[1] + 0x2, g_Data16) && (g_Data16 & ~0xFF00) != 0xFF)
			{
				READ8(Address[1] + 0x2, g_Data8);
				g_Data8 &= 0x00;
				g_Data8 += 0xFF;
				WRITE8(Address[1] + 0x2, g_Data8);
			}
			
			if (READ16(Address[1] + 0x3, g_Data16) && (g_Data16 & ~0xFF00) != 0xFF)
			{
				READ8(Address[1] + 0x3, g_Data8);
				g_Data8 &= 0x00;
				g_Data8 += 0xFF;
				WRITE8(Address[1] + 0x3, g_Data8);
			}
			
			if (READ16(Address[1] + 0x4, g_Data16) && (g_Data16 & ~0xFF00) != 0xFF)
			{
				READ8(Address[1] + 0x4, g_Data8);
				g_Data8 &= 0x00;
				g_Data8 += 0xFF;
				WRITE8(Address[1] + 0x4, g_Data8);
			}
			
			if (READ16(Address[1] + 0x5, g_Data16) && (g_Data16 & ~0xFF00) != 0xFF)
			{
				READ8(Address[1] + 0x5, g_Data8);
				g_Data8 &= 0x00;
				g_Data8 += 0xFF;
				WRITE8(Address[1] + 0x5, g_Data8);
			}
			
			if (READ16(Address[1] + 0x6, g_Data16) && (g_Data16 & ~0xFF00) != 0xFF)
			{
				READ8(Address[1] + 0x6, g_Data8);
				g_Data8 &= 0x00;
				g_Data8 += 0xFF;
				WRITE8(Address[1] + 0x6, g_Data8);
			}
			
			if (READ16(Address[1] + 0x7, g_Data16) && (g_Data16 & ~0xFF00) != 0xF3)
			{
				READ8(Address[1] + 0x7, g_Data8);
				g_Data8 &= 0x00;
				g_Data8 += 0xF3;
				WRITE8(Address[1] + 0x7, g_Data8);
			}
			
			if (READ16(Address[1] + 0x8, g_Data16) && (g_Data16 & ~0xFF00) != 0xFB)
			{
				READ8(Address[1] + 0x8, g_Data8);
				g_Data8 &= 0x00;
				g_Data8 += 0xFB;
				WRITE8(Address[1] + 0x8, g_Data8);
			}
			
			if (READ16(Address[1] + 0x9, g_Data16) && (g_Data16 & ~0xFF00) != 0x81)
			{
				READ8(Address[1] + 0x9, g_Data8);
				g_Data8 &= 0x00;
				g_Data8 += 0x81;
				WRITE8(Address[1] + 0x9, g_Data8);
			}
		}
	}
	
	void RepelLastsForever(MenuEntry *entry)
	{
		static u32 Address = AutoGame(0x464108, 0x464100);
		
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
			0x8C83D30,
			0x8C83D94,
			0x0114518
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
		static u32 Address = 0x37A140;
		
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
			0x419A34,
			0x41A2A4
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