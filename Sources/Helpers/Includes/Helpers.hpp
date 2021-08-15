#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <CTRPluginFramework.hpp>
#include <cmath>
#include <algorithm>
#include "HotkeyHelpers.hpp"
#include "KeyboardHelpers.hpp"

#define PkmnX 1
#define PkmnY 2
#define PkmnXY 3

#define PkmnOR 4
#define PkmnAS 5
#define PkmnORAS 6

#define PkmnS 7
#define PkmnM 8
#define PkmnSM 9

#define PkmnUS 10
#define PkmnUM 11
#define PkmnUSUM 12

#define UnsupportedVer 1

namespace CTRPluginFramework
{
	extern u8 g_Data8;
	extern u8 g_Offset8;
	
	extern u16 g_Data16;
	extern u16 g_Offset16;
	
	extern u32 g_Data32;
	extern u32 g_Offset32;
	
	extern std::string Bin;
	extern std::string Pk6;
	extern std::string Pk7;
	extern std::string Path;
	extern std::string Game;
	
	extern int GameID;
	extern int GamesetID;
	extern int VersionID;
	
	extern bool IsCompatible(void);
	extern bool IsOnWhiteList(void);
	
	extern u32 AutoGame(u32 Title1, u32 Title2);
	extern bool IsInArray(int Val, const int *Arr, int Size);
}

#include "PK67.hpp"

// Shortcuts for the standard CTRPluginFramework read and write
#define WRITE8(Address, Value) Process::Write8(Address, Value)
#define WRITE16(Address, Value) Process::Write16(Address, Value)
#define WRITE32(Address, Value) Process::Write32(Address, Value)
#define WRITE64(Address, Value) Process::Write64(Address, Value)

#define WRITEFLOAT(Address, Value) Process::WriteFloat(Address, Value)
#define WRITEDOUBLE(Address, Value) Process::WriteDouble(Address, Value)
#define WRITESTRING(Address, Value) Process::WriteString(Address, Value)

#define READ8(Address, Value) Process::Read8(Address, Value)
#define READ16(Address, Value) Process::Read16(Address, Value)
#define READ32(Address, Value) Process::Read32(Address, Value)
#define READ64(Address, Value) Process::Read64(Address, Value)

#define READFLOAT(Address, Value) Process::ReadFloat(Address, Value)
#define READDOUBLE(Address, Value) Process::ReadDouble(Address, Value)
#define READSTRING(Address, Value, Size, Format) Process::ReadString(Address, Value, Size, Format)

#ifndef WRITEU8
#define WRITEU8(Address, Value) *(vu8*)(Address) = Value
#endif

#ifndef WRITEU16
#define WRITEU16(Address, Value) *(vu16*)(Address) = Value
#endif

#ifndef WRITEU32
#define WRITEU32(Address, Value) *(vu32*)(Address) = Value
#endif

#ifndef WRITEFLOAT
#define WRITEFLOAT(Address, Value) *(volatile float *)Address = (float)Value
#endif

#ifndef READU8
#define READU8(Address) *(volatile unsigned char*)(Address)
#endif

#ifndef READU16
#define READU16(Address) *(volatile unsigned short*)(Address)
#endif

#ifndef READU32
#define READU32(Address) *(volatile unsigned int*)(Address)
#endif

#ifndef READFLOAT
#define READFLOAT(Address) *(volatile float *)(Address)
#endif

#endif