#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

s32 func_00328448(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0xA0);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00328458);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00328478);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003284A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003284C8);
