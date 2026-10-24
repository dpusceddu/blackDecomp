#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

s32 func_00326AA0(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x1420) = arg2;
    return arg0;
}

s32 func_00326AB0(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x1420);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00326AC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00326AF0);
