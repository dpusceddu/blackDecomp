#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_0011D430();

s32 func_0011F8F8(s32 arg0) {
    return func_0011D430(arg0, 8);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0011F918);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0011FA90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0011FAE0);
