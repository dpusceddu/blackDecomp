#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0018BE88();

s32 func_0018C088(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_0018BE88(arg0, 0x16);
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    return temp_v0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018C0C0);
