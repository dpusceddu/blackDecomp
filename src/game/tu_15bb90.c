#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00155018();

s32 func_0015BB90(s32 arg0) {
    M2C_FIELD(arg0, f32 *, 0x2C) = 1.0f;
    M2C_FIELD(arg0, s8 *, 0x43) = -1;
    M2C_FIELD(arg0, s8 *, 0x45) = 0;
    M2C_FIELD(arg0, s8 *, 0x46) = 0;
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    M2C_FIELD(arg0, s64 *, 0x30) = 0;
    func_00155018(arg0);
    return 1;
}
