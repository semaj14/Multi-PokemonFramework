#ifndef PK6_HPP
#define PK6_HPP

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "types.h"

using namespace CTRPluginFramework;

struct PK6
{
    u32 EncryptionConstant;
    u16 Sanity;
    u16 Checksum;

    // Block A
    u16 Species;
    u16 HeldItem;
    u16 TID;
    u16 SID;
    u32 EXP;
    u8  Ability;
    u8  AbilityNumber;
    u8  TrainingBagHits;
    u8  TrainingBag;
    u32 PID;
    u8  Nature;
    u8  FatefulEncounter_Gender_Form;
    u8  EV_HP;
    u8  EV_ATK;
    u8  EV_DEF;
    u8  EV_SPE;
    u8  EV_SPA;
    u8  EV_SPD;
    u8  CNT_Cool;
    u8  CNT_Beauty;
    u8  CNT_Cute;
    u8  CNT_Smart;
    u8  CNT_Tough;
    u8  CNT_Sheen;
    u8  MarkValue;
    u8  PKRS;
    u8  ST1;
    u8  ST2;
    u8  ST3;
    u8  ST4;
    u8  RIB0;
    u8  RIB1;
    u8  RIB2;
    u8  RIB3;
    u8  RIB4;
    u8  RIB5;
    u8  Unused_1[2];
    u8  RibbonCountMemoryContest;
    u8  RibbonCountMemoryBattle;
    u16 DistByte;
    u32 FormArgument;
    u8  unused_2[2];
    
    // Block B
    u8  Nickname[26];
    u16 Move1;
    u16 Move2;
    u16 Move3;
    u16 Move4;
    u8  Move1_PP;
    u8  Move2_PP;
    u8  Move3_PP;
    u8  Move4_PP;
    u8  Move1_PPUps;
    u8  Move2_PPUps;
    u8  Move3_PPUps;
    u8  Move4_PPUps;
    u16 RelearnMove1;
    u16 RelearnMove2;
    u16 RelearnMove3;
    u16 RelearnMove4;
    u8  SecretSuperTrainingUnlockled;
    u8  unused_3;
    u32 IV32;
    
    // Block C
    u8  HT_Name[26];
    u8  HT_Gender;
    u8  CurrentHandler;
    u8  Geo1_Region;
    u8  Geo1_Country;
    u8  Geo2_Region;
    u8  Geo2_Country;
    u8  Geo3_Region;
    u8  Geo3_Country;
    u8  Geo4_Region;
    u8  Geo4_Country;
    u8  Geo5_Region;
    u8  Geo5_Country;
    u8  unused_4[4];
    u8  HT_Friendship;
    u8  HT_Affection;
    u8  HT_Intensity;
    u8  HT_Memory;
    u8  HT_Feeling;
    u8  unused_5;
    u16 HT_TextVar;
    u8  unused_6[4];
    u8  Fullness;
    u8  Enjoyment;
    
    // Block D
    u8  OT_Name[24];
    u8  OT_Friendship;
    u8  OT_Affection;
    u8  OT_Intensity;
    u8  OT_Memory;
    u16 OT_TextVar;
    u8  OT_Feeling;
    u8  Egg_Year;
    u8  Egg_Month;
    u8  Egg_YearDay;
    u8  Met_Year;
    u8  Met_Month;
    u8  Met_Day;
    u8  unused_7;
    u16 Egg_Location;
    u16 Met_Location;
    u8  Ball;
    u8  Met_Level_OT_Gender;
    u8  GroundTile;
    u8  Version;
    u8  Country;
    u8  Region;
    u8  ConsoleRegion;
    u8  Language;
    u8  unused_8[4];
};

struct PK7
{
    u32 EncryptionConstant;
    u16 Sanity;
    u16 Checksum;

    // Block A
    u16 Species;
    u16 HeldItem;
    u16 TID;
    u16 SID;
    u32 EXP;
    u8  Ability;
    u8  AbilityNumber;
    u8  MarkValue;
    u32 PID;
    u8  Nature;
    u8  FatefulEncounter_Gender_Form;
    u8  EV_HP;
    u8  EV_ATK;
    u8  EV_DEF;
    u8  EV_SPE;
    u8  EV_SPA;
    u8  EV_SPD;
    u8  CNT_Cool;
    u8  CNT_Beauty;
    u8  CNT_Cute;
    u8  CNT_Smart;
    u8  CNT_Tough;
    u8  CNT_Sheen;
    u8  ResortEventStatus;
    u8  PKRS;
    u8  ST1;
    u8  ST2;
    u8  ST3;
    u8  ST4;
    u8  RIB0;
    u8  RIB1;
    u8  RIB2;
    u8  RIB3;
    u8  RIB4;
    u8  RIB5;
    u8  RIB6;
    u8  Unused_1;
    u8  RibbonCountMemoryContest;
    u8  RibbonCountMemoryBattle;
    u16 DistByte;
    u32 FormArgument;
    u8  unused_2[2];
    
    // Block B
    u8  Nickname[26];
    u16 Move1;
    u16 Move2;
    u16 Move3;
    u16 Move4;
    u8  Move1_PP;
    u8  Move2_PP;
    u8  Move3_PP;
    u8  Move4_PP;
    u8  Move1_PPUps;
    u8  Move2_PPUps;
    u8  Move3_PPUps;
    u8  Move4_PPUps;
    u16 RelearnMove1;
    u16 RelearnMove2;
    u16 RelearnMove3;
    u16 RelearnMove4;
    u8  SecretSuperTrainingUnlockled;
    u8  unused_3;
    u32 IV32;
    
    // Block C
    u8  HT_Name[26];
    u8  HT_Gender;
    u8  CurrentHandler;
    u8  Geo1_Region;
    u8  Geo1_Country;
    u8  Geo2_Region;
    u8  Geo2_Country;
    u8  Geo3_Region;
    u8  Geo3_Country;
    u8  Geo4_Region;
    u8  Geo4_Country;
    u8  Geo5_Region;
    u8  Geo5_Country;
    u8  unused_4[4];
    u8  HT_Friendship;
    u8  HT_Affection;
    u8  HT_Intensity;
    u8  HT_Memory;
    u8  HT_Feeling;
    u8  unused_5;
    u16 HT_TextVar;
    u8  unused_6[4];
    u8  Fullness;
    u8  Enjoyment;
    
    // Block D
    u8  OT_Name[24];
    u8  OT_Friendship;
    u8  OT_Affection;
    u8  OT_Intensity;
    u8  OT_Memory;
    u16 OT_TextVar;
    u8  OT_Feeling;
    u8  Egg_Year;
    u8  Egg_Month;
    u8  Egg_YearDay;
    u8  Met_Year;
    u8  Met_Month;
    u8  Met_Day;
    u8  unused_7;
    u16 Egg_Location;
    u16 Met_Location;
    u8  Ball;
    u8  Met_Level_OT_Gender;
    u8  HyperTrainFlags;
    u8  Version;
    u8  Country;
    u8  Region;
    u8  ConsoleRegion;
    u8  Language;
    u8  unused_8[4];
};

#define PK6_size 232
#define G6_MaxSpecies 721
#define G7_MaxSpecies 802

const u8 blockPosition[4][24] = 
{
    {0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3},
    {1, 1, 2, 3, 2, 3, 0, 0, 0, 0, 0, 0, 2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2},
    {2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2, 0, 0, 0, 0, 0, 0, 3, 2, 3, 2, 1, 1},
    {3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0}
};

void unshuffle(u8* shuffled, u8* pkm, u32 sv);

template <class PKX> 
void decryptPokemon(u8* ekm, PKX* poke) 
{
    // ENCRYPTION KEY FROM FIRST 4 BYTES OF EKM
    u32 pkval = *(u32*)ekm;

    // SHUFFLE VALUE USED TO UNSHUFFLE THE DATA
    u32 shval = (((pkval >> 0xD) & 0x1F) % 24);

    // GET INITIAL SEED FROM FIRST 4 BYTES, SAME AS ENC KEY
    u32 seed = pkval;

    // DECRYPT DATA USING SEED
    u16 a;
    u16 b;
    for(int i = 8; i < PK6_size; i += 2) 
    {
        seed = (0x41C64E6D * seed) + 0x00006073;
        ekm[i] ^= (u8)(seed >> 16);
        ekm[i + 1] ^= (u8)(seed >> 24);
    }

    // UNSHUFFLE BLOCK DATA
    unshuffle(ekm, (u8*)poke, shval);
}

template <class PKX>
void encryptPokemon(PKX* poke, u8* ekm)
{
    // ENCRYPTION KEY FROM FIRST 4 BYTES OF EKM
    u32 pkval = *(u32*)ekm;

    // SHUFFLE VALUE USED TO RESHUFFLE THE DATA
    u32 shval = (((pkval >> 0xD) & 0x1F) % 24);

    // GET INITIAL SEED FROM FIRST 4 BYTES, SAME AS ENC KEY
    u32 seed = pkval;

    // RESHUFFLE BLOCK DATA
    for (int i = 0; i < 11; i++)
    {
        unshuffle(ekm, (u8*)poke, shval);
        if (!Process::CopyMemory(ekm, poke, PK6_size)) return;
    }

    // ENCRYPT DATA USING SEED        
    u16 a;
    u16 b;
    for(int i = 8; i < PK6_size; i += 2) 
    {
        seed = (0x41C64E6D * seed) + 0x00006073;
        ekm[i] ^= (u8)(seed >> 16);
        ekm[i + 1] ^= (u8)(seed >> 24);
    }
}

template <class PKX>
u16 checksum(PKX* poke)
{
    u16 chksum = 0;
    for(u8 i = 4; i < PK6_size/2; i++) 
    {
        chksum += *((u16*)(poke) + i);
    }
    return chksum;
} 

template <class PKX>
bool isValid(PKX* poke) 
{
    // 1. Ensure sanity check
    if(!poke || poke->Sanity)
        return false;

    // 2. Calculate checksum
    if(checksum(poke) != poke->Checksum)
        return false;

    // 3. Ensure species is in a valid range.
    return (poke->Species >= 1 && poke->Species <= (CTRPluginFramework::GamesetID == PkmnXY || CTRPluginFramework::GamesetID == PkmnORAS ? G6_MaxSpecies : G7_MaxSpecies));
}

template <class PKX>
bool getPokemon(u32 PokemonPointer, PKX* poke)
{
    if(poke == 0 || PokemonPointer == 0) return false;

    // LOAD ENCRYPTED GAME DATA TO EKM
    u8 ekm[PK6_size];
    if(!Process::CopyMemory(&ekm, (u8*)PokemonPointer, PK6_size)) return false;

    // DECRYPT DATA AND STORE IN STRUCT
    decryptPokemon(ekm, poke);

    // CHECK VALIDITY AND RETURN CHECK
    return (isValid(poke));
}

template <class PKX>
bool setPokemon(u32 PokemonPointer, PKX* poke)
{
    if(poke == 0 || PokemonPointer == 0) return false;

    // FIX CHECKSUM
    poke->Checksum = checksum(poke);

    // LOAD DECRYPTED STRUCT DATA TO EKM
    u8 ekm[PK6_size];
    if (!Process::CopyMemory(&ekm, poke, PK6_size)) return false;

    // ENCRYPT DATA AND STORE IN ARRAY
    encryptPokemon(poke, ekm);

    // WRITE ARRRAY DATA TO GAME
    return (Process::Patch(PokemonPointer, ekm, PK6_size));
}

template <class PKX>
void makeShiny(PKX* poke)
{
    u16 s_xor = (poke->TID ^ poke->SID ^ (u16)(poke->PID & 0x0000FFFF)) & 0xFFF0;
    poke->PID = (poke->PID & 0x000FFFFF) | (s_xor << 16);
}

template <class PKX>
u8 isShiny(PKX* poke)
{
    return (poke->TID ^ poke->SID ^ (u16)(poke->PID & 0x0000FFFF) ^ (u16)((poke->PID & 0xFFFF0000) >> 16)) < 16;
}

#endif