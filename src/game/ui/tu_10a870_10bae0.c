#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_0010BAE0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;

    temp_2 = arg0 + 0x5E4;
    M2C_FIELD(arg0, s32 *, 0x5E4) = arg2;
    M2C_FIELD(arg0, s32 *, 0x590) = temp_2;
    M2C_FIELD(arg0, s32 *, 0x59C) = arg1;
    M2C_FIELD(arg0, s32 *, 0x5E0) = arg1;
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010BAF8);
