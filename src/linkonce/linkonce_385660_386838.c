#include "ps2/prelude.h"

s32 func_00386838(void *arg0, s32 arg1) {
    s32 temp_2;
    s32 temp_5;

    temp_2 = M2C_FIELD(arg0, s32 *, 0);
    temp_5 = arg1 + 0x14;
    return ((temp_5 ^ (temp_2 + (M2C_FIELD(arg0, s32 *, 0x10) * 0x14))) != 0) ? temp_5 : temp_2;
}

s32 func_00386860(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x80);
}
