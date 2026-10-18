#include "auto/prelude.h"

#include "types_ghidra.h"

s32 func_003283F8(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, u16 *, 0x5C) = (u16) (M2C_FIELD(arg0, u16 *, 0x5C) | 1);
    M2C_FIELD(arg0, f32 *, 0x98) = (f32) M2C_FIELD(arg2, f32 *, 0);
    return arg0;
}
