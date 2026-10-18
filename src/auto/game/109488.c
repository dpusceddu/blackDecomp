#include "auto/prelude.h"

void func_00109488(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    void *temp_4;

    temp_4 = (arg1 * 0x140) + arg0;
    M2C_FIELD(temp_4, s32 *, 0x130) = arg5;
    M2C_FIELD(temp_4, s8 *, 0x139) = 1;
    M2C_FIELD(temp_4, s32 *, 0xC) = 1;
    M2C_FIELD(temp_4, s32 *, 0x11C) = arg2;
    M2C_FIELD(temp_4, s32 *, 0x128) = arg3;
    M2C_FIELD(temp_4, s32 *, 0x12C) = arg4;
    M2C_FIELD(temp_4, s8 *, 0x13C) = 0;
}
