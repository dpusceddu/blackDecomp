#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_003BCAC8;

void func_00124D98(s32 arg0, s32 arg1) {
    D_003BCAC8 = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00124DA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00124DF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00124E00);
