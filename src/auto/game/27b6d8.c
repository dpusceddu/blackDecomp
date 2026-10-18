#include "auto/prelude.h"

extern s32 func_0027BA68();
extern s32 func_0027B688();

s32 func_0027B6D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_18;
    void *temp_4;

    temp_18 = func_0027BA68(arg2, arg3, arg4);
    temp_4 = M2C_FIELD(arg0, s32 *, 8) + (func_0027B688(arg0) << 5);
    M2C_FIELD(temp_4, s32 *, 0xC) = arg2;
    M2C_FIELD(temp_4, s32 *, 0x10) = arg3;
    M2C_FIELD(temp_4, s32 *, 0x14) = arg4;
    M2C_FIELD(temp_4, s32 *, 0x18) = temp_18;
    M2C_FIELD(temp_4, s8 *, 0x1D) = (s8) arg5;
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + 1);
    return (s32) temp_4;
}
