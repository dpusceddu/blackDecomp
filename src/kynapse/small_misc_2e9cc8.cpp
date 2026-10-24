#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/small_misc.hpp"

// /SLUS_213.76 0x2e9cc8

void Kaim_ReleaseService()
{
    if (gService)
        delete gService;
    gService = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E9D10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E9D50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E9DB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E9E20);
