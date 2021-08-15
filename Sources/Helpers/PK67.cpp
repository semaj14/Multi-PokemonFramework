#include <CTRPluginFramework.hpp>

#include "PK67.hpp"
#include "Helpers.hpp"
#include "KeyboardHelpers.hpp"

using namespace CTRPluginFramework;

u8 blockPosition[4][24] = 
{
    {0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3},
    {1, 1, 2, 3, 2, 3, 0, 0, 0, 0, 0, 0, 2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2},
    {2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2, 0, 0, 0, 0, 0, 0, 3, 2, 3, 2, 1, 1},
    {3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0}
};

u32 lcrng(u32 seed) 
{
    return (seed * 0x41C64E6D + 0x00006073);
}


void unshuffle(u8* shuffled, u8* pkm, u32 sv) 
{
    memcpy(pkm, shuffled, PK6_size);
    for(short block = 0; block < 4; block++)
    {
        for(short b = 0; b < 56; b++) 
        {
            *(pkm + b + 8 + 56 * block) = *(shuffled + b + 8 + 56 * blockPosition[block][sv]);
        }
    }
}

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
    return (poke->Species >= 1 && poke->Species <= (GamesetID == PkmnXY || GamesetID == PkmnORAS ? G6_MaxSpecies : G7_MaxSpecies));
}

template <class PKX>
void getPokemon(u32 PokemonPointer, PKX* poke)
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
void setPokemon(u32 PokemonPointer, PKX* poke)
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