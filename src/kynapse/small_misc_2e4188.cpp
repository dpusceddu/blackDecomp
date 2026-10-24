#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/small_misc.hpp"

// /SLUS_213.76 0x2e4188

bool Kaim_GetFlag()
{
    return gFlag;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E4198);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E41B8);
