#include "auto/prelude.h"

extern s32 func_002AC628();

s32 func_0027B390(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;
    s32 temp_5;

    func_002AC628(M2C_FIELD(arg0, s32 *, 0x60), M2C_FIELD(arg1, s32 *, 0x60), arg2);
    temp_5 = M2C_FIELD(arg1, s32 *, 0x64);
    if (temp_5 != 0) {
        func_002AC628(M2C_FIELD(arg0, s32 *, 0x64), temp_5, arg2);
    }
    M2C_FIELD(arg0, s32 *, 0x78) = (s32) M2C_FIELD(arg2, s32 *, 8);
    M2C_FIELD(arg0, s32 *, 0x7C) = (s32) M2C_FIELD(arg2, s32 *, 0xC);
    temp_2 = M2C_FIELD(arg1, s32 *, 0x80);
    M2C_FIELD(arg0, s32 *, 0x80) = temp_2;
    return temp_2;
}
