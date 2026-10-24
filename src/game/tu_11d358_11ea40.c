#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_0011D430();

void func_0011EA40(void) {

}

s32 func_0011EA48(s32 arg0) {
    return func_0011D430(arg0, 6);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0011EA68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0011EB08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0011EB88);
