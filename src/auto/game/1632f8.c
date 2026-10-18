#include "auto/prelude.h"

void func_001632F8(void *arg0, s32 arg1, s32 arg2, s128 arg3, s128 arg4, s8 arg5, f32 fparg0, f32 fparg1) {
    M2C_FIELD(arg0, s128 *, 0x10) = arg4;
    M2C_FIELD(arg0, s32 *, 0x20) = arg1;
    M2C_FIELD(arg0, s8 *, 0x2D) = arg5;
    M2C_FIELD(arg0, f32 *, 0x28) = fparg1;
    M2C_FIELD(arg0, s8 *, 0x2C) = 1;
    M2C_FIELD(arg0, s128 *, 0) = arg3;
    M2C_FIELD(arg0, f32 *, 0x24) = (f32) (fparg0 / 144.0f);
}
