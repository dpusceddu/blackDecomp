#include "include_asm.h"

#include "game/weapons/reserves.hpp"

namespace ModWeapons {
extern "C" EeU16 D_003F5310[10];

void Reserves::Initialize()
{
    for(EeU8 i=0;i<10;++i) reserve[i]=D_003F5310[i];
    entries=0;
    count=0;
}

int Reserves::Reset()
{
    EeU8 i;
    for(i=0;i<10;++i) reserve[i]=D_003F5310[i];
    for(i=0;i<count;++i) ((EeU8*)entries)[i]=0;
    return 1;
}
}
