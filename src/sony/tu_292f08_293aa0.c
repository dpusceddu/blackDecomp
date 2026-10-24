#include "ps2/prelude.h"

extern s32 D_00443680;

s32 func_00293AA0(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = D_00443680;
    M2C_FIELD(arg1, s32 *, 0xC) = arg0;
    M2C_FIELD(arg1, s32 *, 0x14) = temp_2;
    D_00443680 = arg1;
    M2C_FIELD(arg1, s32 *, 8) = arg0;
    M2C_FIELD(arg1, s32 *, 4) = 0;
    M2C_FIELD(arg1, s32 *, 0) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    return temp_2;
}
