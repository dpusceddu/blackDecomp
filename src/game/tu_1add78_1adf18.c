#include "ps2/prelude.h"

void func_001ADF18(void *arg0, s32 arg1) {
    M2C_FIELD(((arg1 * 4) + M2C_FIELD(arg0, s32 *, 4)), s32 *, 0) = 0;
}

void func_001ADF30(void *arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = arg1 * 4;
    M2C_FIELD((temp_5 + M2C_FIELD(arg0, s32 *, 4)), s32 *, 0) = M2C_FIELD((temp_5 + M2C_FIELD(arg0, s32 *, 0)), s32 *, 0);
}
