#include "ps2/prelude.h"

s32 func_00180ED8(s32 arg0) {
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 0x100);
    if (M2C_FIELD(temp_5, s32 *, 0x14) == 1) {
        goto block_2;
    }
    goto block_4;
block_2:
    return 0;
block_4:
    if (M2C_FIELD(temp_5, u8 *, 0x71) == 0) {
        goto block_6;
    }
    return 0;
block_6:
    return arg0 + 0x20;
}

void func_00180F10(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
}

s32 func_00180F18(s8 *arg0) {
    *arg0 = 0;
    return 1;
}
