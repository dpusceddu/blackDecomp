#include "ps2/prelude.h"

extern s32 func_0026CA20();

void func_001078D8(s32 arg0, s8 arg1) {
    M2C_FIELD((arg0 + arg1), s8 *, 0x79D) = 1;
}

s32 func_001078F0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = func_0026CA20(arg0, arg1);
    M2C_FIELD(arg0, s8 *, 0x79C) = (s8) arg1;
    return temp_v0;
}
