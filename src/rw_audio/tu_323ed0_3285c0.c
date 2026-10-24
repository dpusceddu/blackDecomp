#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

s32 func_003285C0(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0xA4);
    return arg0;
}

s32 func_003285D0(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0xBC) == 0);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003285E8);
