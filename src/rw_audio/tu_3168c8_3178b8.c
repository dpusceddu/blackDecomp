#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0040E1D0;

void func_003178B8(s32 arg0) {
    D_0040E1D0 = arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003178F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00318078);
