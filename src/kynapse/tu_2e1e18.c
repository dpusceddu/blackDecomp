#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 (*D_00451250)();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1E18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1FD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E2098);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E22F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E2638);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E27A8);

s32 func_002E27D0(void) {
    return D_00451250() & 0xFF;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E27F8);
