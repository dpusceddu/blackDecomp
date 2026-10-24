#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_0019F470();

s32 func_0019EF80(s32 arg0) {
    return func_0019F470(arg0, 1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019EFA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019F0E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019F228);
