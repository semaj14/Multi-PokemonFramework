#include <CTRPluginFramework.hpp>

#include "Includes/Helpers.hpp"

using namespace CTRPluginFramework;

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