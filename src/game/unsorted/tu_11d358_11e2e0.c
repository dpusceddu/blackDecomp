#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0011E1B8();

s32 func_0011E2E0(s32 arg0) {
    u8 sp[8] __attribute__((aligned(16)));
    return func_0011E1B8(arg0, (s32) sp);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0011E300);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0011E3A8);
