#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0040E824;

void func_0032AB18(s32 arg0) {
    D_0040E824 = arg0;
}

s32 func_0032AB20(void) {
    return D_0040E824;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0032AB28);
