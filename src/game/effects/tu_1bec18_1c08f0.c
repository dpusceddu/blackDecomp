#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001B0FF8();

s32 func_001C08F0(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x50) = 0;
    return func_001B0FF8(arg0);
}

