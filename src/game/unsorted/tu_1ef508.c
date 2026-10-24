#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00280A08();

s32 func_001EF508(s32 arg0) {
    s32 temp_v0;

    M2C_FIELD(arg0, s32 *, 0x248) = 0;
    M2C_FIELD(arg0, s32 *, 0x24C) = 0;
    M2C_FIELD(arg0, f32 *, 0x250) = 1.0f;
    temp_v0 = func_00280A08(arg0);
    M2C_FIELD(arg0, s32 *, 0x244) = 0;
    return temp_v0;
}
