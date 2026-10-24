#include "game/weapons/reserves.hpp"

namespace ModWeapons {
extern "C" const EeU16 D_003F5328[10];

void Reserves::Return(int index,EeU16 amount)
{
    reserve[index]+=amount;
    if(reserve[index]>D_003F5328[index]) reserve[index]=D_003F5328[index];
}

int Reserves::AtMaximum(int index)
{
    return reserve[index]==D_003F5328[index];
}
}
