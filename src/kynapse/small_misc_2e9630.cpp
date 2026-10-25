#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/small_misc.hpp"

// /SLUS_213.76 0x2e9630

float FloatTable::GetValue(int index)
{
    return values[index];
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E96F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E97B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E9BC8);
