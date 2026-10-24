#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193990();

s32 func_00198CF8(s32 arg0) {
    return func_00193990(arg0, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00198D18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00198D40);
