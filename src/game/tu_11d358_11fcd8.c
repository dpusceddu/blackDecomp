#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_0011D430();

s32 func_0011FCD8(s32 arg0) {
    return func_0011D430(arg0, 3);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0011FCF8);
