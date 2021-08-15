#include <CTRPluginFramework.hpp>
#include "Includes/Helpers.hpp"

namespace CTRPluginFramework
{
	u8 g_Data8;
	u8 g_Offset8;
	
	u16 g_Data16;
	u16 g_Offset16;
	
	u32 g_Data32;
	u32 g_Offset32;
	
	std::string Bin;
	std::string Pk6;
	std::string Pk7;
	std::string Path;
	std::string Game;
	
	int GameID = 0;
	int GamesetID = 0;
	int VersionID = 0;
	
	// Checks to see if the game is compatible with the plugin or i as well as returns 3 different values based on the version and game
	bool IsCompatible(void)
	{
		u64 TID = Process::GetTitleID();
		u16 VID = Process::GetVersion();
		
		switch (TID)
		{
			case 0x0004000000055D00: // Pokemon X
			{
				// Version must be 1.5 (latest version)
				if (VID != 5232)
					VersionID = UnsupportedVer;
				
				Bin = "/luma/plugins/0004000000055D00/Bin/";
				Pk6 = "/luma/plugins/0004000000055D00/Pk6/";
				Path = "/luma/plugins/0004000000055D00/";
				Game = "Pokémon X";
				GameID = PkmnX;
				GamesetID = PkmnXY;
				return true;
			}
			break;
			
			case 0x0004000000055E00: // Pokemon Y
			{
				// Version must be 1.5 (latest version)
				if (VID != 5216)
					VersionID = UnsupportedVer;
				
				Bin = "/luma/plugins/0004000000055E00/Bin/";
				Pk6 = "/luma/plugins/0004000000055E00/Pk6/";
				Path = "/luma/plugins/0004000000055E00/";
				Game = "Pokémon Y";
				GameID = PkmnY;
				GamesetID = PkmnXY;
				return true;
			}
			break;
			
			case 0x000400000011C400: // Pokemon Omega Ruby
			{
				// Version must be 1.4 (latest version)
				if (VID != 7280)
					VersionID = UnsupportedVer;
				
				Bin = "/luma/plugins/000400000011C400/Bin/";
				Pk6 = "/luma/plugins/000400000011C400/Pk6/";
				Path = "/luma/plugins/000400000011C400/";
				Game = "Pokémon Omega Ruby";
				GameID = PkmnOR;
				GamesetID = PkmnORAS;
				return true;
			}
			break;
			
			case 0x000400000011C500: // Pokemon Alpha Sapphire
			{
				// Version must be 1.4 (latest version)
				if (VID != 7280)
					VersionID = UnsupportedVer;
				
				Bin = "/luma/plugins/000400000011C500/Bin/";
				Pk6 = "/luma/plugins/000400000011C500/Pk6/";
				Path = "/luma/plugins/000400000011C500/";
				Game = "Pokémon Alpha Sapphire";
				GameID = PkmnAS;
				GamesetID = PkmnORAS;
				return true;
			}
			break;
			
			case 0x0004000000164800: // Pokemon Sun
			{
				// Version must be 1.2 (latest version)
				if (VID != 2112)
					VersionID = UnsupportedVer;
				
				Bin = "/luma/plugins/0004000000164800/Bin/";
				Pk7 = "/luma/plugins/0004000000164800/Pk7/";
				Path = "/luma/plugins/0004000000164800/";
				Game = "Pokémon Sun";
				GameID = PkmnS;
				GamesetID = PkmnSM;
				return true;
			}
			break;
			
			case 0x0004000000175E00: // Pokemon Moon
			{
				// Version must be 1.2 (latest version)
				if (VID != 2112)
					VersionID = UnsupportedVer;
				
				Bin = "/luma/plugins/0004000000175E00/Bin/";
				Pk7 = "/luma/plugins/0004000000175E00/Pk7/";
				Path = "/luma/plugins/0004000000175E00/";
				Game = "Pokémon Moon";
				GameID = PkmnM;
				GamesetID = PkmnSM;
				return true;
			}
			break;
			
			case 0x00040000001B5000: // Pokemon Ultra Sun
			{
				// Version must be 1.2 (latest version)
				if (VID != 2080)
					VersionID = UnsupportedVer;
				
				Bin = "/luma/plugins/00040000001B5000/Bin/";
				Pk6 = "/luma/plugins/00040000001B5000/Pk7/";
				Path = "/luma/plugins/00040000001B5000/";
				Game = "Pokémon Ultra Sun";
				GameID = PkmnUS;
				GamesetID = PkmnUSUM;
				return true;
			}
			break;
			
			case 0x00040000001B5100: // Pokemon Ultra Moon
			{
				// Version must be 1.2 (latest version)
				if (VID != 2080)
					VersionID = UnsupportedVer;
				
				Bin = "/luma/plugins/00040000001B5100/Bin/";
				Pk6 = "/luma/plugins/00040000001B5100/Pk7/";
				Path = "/luma/plugins/00040000001B5100/";
				Game = "Pokémon Ultra Moon";
				GameID = PkmnUM;
				GamesetID = PkmnUSUM;
				return true;
			}
			break;
			
			// If the game matches none of the titles above, then abort and return false
			default:
			{
				abort();
				return false;
			}
			break;
		}
		
		return GameID;
		return GamesetID;
		return VersionID;
	}
	
	bool IsOnWhiteList(void)
	{
		FriendKey FKey;
		FriendKey *FKeyPointer = &FKey;
		
		u64 FriendCode;
		u64 *FriendCodePointer = &FriendCode;
		
		frdInit();
		FRD_GetMyFriendKey(FKeyPointer);
		FRD_PrincipalIdToFriendCode(FKey.principalId, FriendCodePointer);
		
		std::vector<std::string> FriendCodes;
		
		if (std::find(FriendCodes.begin(), FriendCodes.end(), std::to_string(*FriendCodePointer)) == FriendCodes.end())
		{
			abort();
			return false;
		}
		
		else return true;
	}
	
	// Takes two arguments and returns the one for the current game
	u32 AutoGame(u32 Title1, u32 Title2)
	{
		if (GameID == PkmnX || GameID == PkmnOR || GameID == PkmnS || GameID == PkmnUS)
			return Title1;
		
		if (GameID == PkmnY || GameID == PkmnAS || GameID == PkmnM || GameID == PkmnUM)
			return Title2;
		
		return 0;
	}
	
	bool IsInArray(int Val, const int *Arr, int Size)
	{
		for (int i = 0; i < (Size); i++)
		{
			if (Arr[i] == Val)
			return true;
		}
		
		return false;
	}
}