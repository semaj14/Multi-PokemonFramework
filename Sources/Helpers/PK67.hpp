#ifndef PK6_HPP
#define PK6_HPP

#include <CTRPluginFramework.hpp>
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

u32 lcrng(u32 seed);
void unshuffle(u8* shuffled, u8* pkm, u32 sv);
void decryptPokemon(u8* ekm, PK6* poke);
void decryptPokemon(u8* ekm, PK7* poke);
void encryptPokemon(PK6* poke, u8* ekm);
void encryptPokemon(PK7* poke, u8* ekm);
u16 checksum(PK6* poke);
u16 checksum(PK7* poke);
bool isValid(PK6* poke);
bool isValid(PK7* poke);
bool getPokemon(u32 PokemonPointer, PK6* poke);
bool getPokemon(u32 PokemonPointer, PK7* poke);
bool setPokemon(u32 PokemonPointer, PK6* poke);
bool setPokemon(u32 PokemonPointer, PK7* poke);
void makeShiny(PK6* poke);
void makeShiny(PK7* poke);
u8 isShiny(PK6* poke);
u8 isShiny(PK7* poke);

#endif