#include <CTRPluginFramework.hpp>

#include "../../Helpers/KeyboardHelpers.hpp"
#include "../../Helpers.hpp"

using namespace CTRPluginFramework;

namespace USUM
{
	void MoonWalk(MenuEntry *entry)
	{
		static u32 Address = AutoGame(0x3AAEB0, 0x3AAEB4);
		
		if (!Controller::IsKeyDown(Key::B))
		{
			if (!WRITEFLOAT(Address, -1.0f))
				goto Error;
		}
		
		Error: return;
	}
	
	void GetWalkAndRunSpeed(MenuEntry *entry)
	{
		float& KBValue = *GetArg<float>(entry);
		Keyboard KB(entry->Name() + ":");
		KB.IsHexadecimal(false);
		KB.SetMaxLength(3);
		KB.SetCompareCallback([](const void *In, std::string &Error)
		{
			float Input = *static_cast<const float *>(In);
			
			if (Input >= 0 && Input <= 1.4)
				return (true);
			
			Error = "The value must be between 0-1.4.";
			return (false);
		});
		
		if (entry->IsActivated())
			KB.Open(KBValue);
	}
	
	void SetWalkAndRunSpeed(MenuEntry *entry)
	{
		float& KBValue = *GetArg<float>(entry);
		
		static u32 Address = AutoGame(0x3AAEB0, 0x3AAEB4);
		
		if (!WRITEFLOAT(Address, KBValue))
			goto Error;
		
		Error: return;
	}
	
    void WalkThroughWalls(MenuEntry *entry)
    {
		static u32 Address[2] =
		{
			AutoGame(0x3AD228, 0x3AD22C),
			AutoGame(0x3AD35C, 0x3AD360)
		};
		
		if (entry->Hotkeys[0].IsDown())
		{
			if (!WRITE32(Address[0], 0xE1A00000))
				goto Error;
			
			if (!WRITE32(Address[1], 0xE1A00000))
				goto Error;
		}
		
		else
		{
			if (!WRITE32(Address[0], 0xEB01F8A0))
				goto Error;
			
			if (!WRITE32(Address[1], 0xEB01F853))
				goto Error;
		}
		
		Error: return;
    }
	
	void RepelLastsForever(MenuEntry *entry)
	{
		static u32 Address = 0x33013958;
		
		if (entry->IsActivated())
			WRITE16(Address, 0x1F4);
		
		if (!entry->IsActivated())
			WRITE16(Address, 0x0);
	}
	
	void CameraZoomOut(MenuEntry *entry)
	{
		static u32 Address[3] =
		{
			0x005BBF80,
			0x0803B920,
			0x005BBF98
		};
		
		static u32 Buffer[7] =
		{
			0xED940A1C, 0xED9F1A03, 0xEE300A01, 0xED840A1C,
			0xE2840004, 0xE12FFF1E, 0x00000000
		};
		
		u32 Temp = 0;
		
		if (entry->WasJustActivated())
		{
			if (!Process::Patch(Address[0], Buffer, 0x1C))
				goto Error;
		}
		
		if (entry->IsActivated())
		{
			if (READ32(Address[1], Temp) && Temp == 0xE2840004)
			{
				if (!WRITE32(Address[1], 0xEBFAA996))
					goto Error;
			}
			
			if (entry->Hotkeys[0].IsPressed())
			{
				if (!WRITE32(Address[2], 0xC4BB8000))
					goto Error;
			}
			
			if (entry->Hotkeys[1].IsPressed())
			{
				if (!WRITE32(Address[2], 0x0))
					goto Error;
			}
		}
		
		Error: return;
	}
	
	void InstantDialogs(MenuEntry *entry)
	{
		static u32 Address[2] =
		{
			AutoGame(0x3D12B4, 0x3D12B8),
			AutoGame(0x3D1B58, 0x3D1B5C)
		};
		
		if (!WRITE32(Address[0], 0xE3A04003))
			goto Error;
		
		if (!WRITE32(Address[1], 0xE3A05003))
			goto Error;
		
		Error: return;
	}
	
    void NoOutlines(MenuEntry *entry)
    {
		static u32 Address = AutoGame(0x42FBA4, 0x42FBA8);
		
		if (entry->IsActivated())
		{
			if (!WRITE32(Address, 0xE320F000))
				goto Error;
		}
		
		else if (!entry->WasJustActivated())
		{
			if (!WRITE32(Address, 0xE5802004))
				goto Error;
		}
		
		Error: return;
    }
	
    void NoPlayerShadow(MenuEntry *entry)
    {
		static u32 Address = AutoGame(0x3AB574, 0x3AB578);
		
		if (entry->IsActivated())
		{
			if (!WRITE32(Address, 0x0))
				goto Error;
		}
		
		else if (!entry->WasJustActivated())
		{
			if (!WRITE32(Address, 0x3F800000))
				goto Error;
		}
		
		Error: return;
    }
	
    void QR100Points(MenuEntry *entry)
    {
		static u32 Address = 0x3307B343;
		
		if (!WRITE8(Address, 0x64))
			goto Error;
		
		Error: return;
    }
	
    void NoQRWaitTime(MenuEntry *entry)
    {
		static u32 Address = AutoGame(0x4553D4, 0x4553D8);
		static u32 Data[1] = {0xE3A00000};
		static u32 Original[1] = {0};
		
		if (entry->WasJustActivated())
		{
			if (!Process::Patch(Address, Data, 0x4, Original))
				goto Error;
		}
		
		else if (!entry->IsActivated())
		{
			if (!Process::Patch(Address, Original, 0x4))
				goto Error;
		}
		
		Error: return;
    }
	
    void DisableNFC(MenuEntry *entry)
    {
		static u32 Address = 0x3F3428;
		
		if (entry->WasJustActivated())
		{
			if (!WRITE32(Address, 0xE3A01000))
				goto Error;
		}
		
		else if (!entry->IsActivated())
		{
			if (!WRITE32(Address, 0xE3A01001))
				goto Error;
		}
		
		Error: return;
    }
}