#include "include_asm.h"
#include "ps2/prelude.h"

extern void * func_001AFD80(void *, s32, s32);

s32 func_00148498(void *arg0, s32 arg1) {
    s32 temp_6;

    temp_6 = arg1 * 0xC;
    return func_001AFD80(M2C_FIELD(arg0, s32 *, 0x1A0) + temp_6, M2C_FIELD(arg0, s32 *, 0x118), temp_6) + 0x90;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001484C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00148508);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00148550);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00148BE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00148D10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00148FF8);
