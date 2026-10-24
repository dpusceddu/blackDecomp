#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

s32 func_00328610(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0x9C);
    return arg0;
}

s32 func_00328620(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x40) = arg2;
    return arg0;
}

s32 func_00328630(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x40);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00328640);
