#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

s32 func_00378C08(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0x138);
    return arg0;
}
