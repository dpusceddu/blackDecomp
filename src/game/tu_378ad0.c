#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

s32 func_00378AD0(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x24C);
    return arg0;
}

s32 func_00378AE0(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x250);
    return arg0;
}

s32 func_00378AF0(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x254);
    return arg0;
}
