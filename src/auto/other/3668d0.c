#include "auto/prelude.h"

extern s32 func_00366468();

s32 func_003668D0(s32 arg0, s32 arg1) {
    void *temp_2;

    temp_2 = func_00366468(arg0, 1);
    M2C_FIELD(temp_2, s32 *, 0x14) = arg1;
    M2C_FIELD(temp_2, s32 *, 0x10) = 1;
    return (s32) temp_2;
}
