#include "auto/prelude.h"

s32 func_00394270(s32 arg0, s32 arg1) {
    s32 temp_3;
    s32 temp_4;
    s32 temp_5;
    s32 temp_6;

    temp_6 = M2C_FIELD(arg1, s32 *, 8);
    temp_3 = M2C_FIELD(arg0, s32 *, 8);
    temp_5 = M2C_FIELD(arg1, s32 *, 0xC);
    if (temp_3 < temp_6) {
        goto block_6;
    }
    if (temp_6 < temp_3) {
        goto block_3;
    }
    temp_4 = M2C_FIELD(arg0, s32 *, 0xC);
    goto block_5;
block_3:
    return 1;
block_5:
    if (temp_4 >= temp_5) {
        goto block_7;
    }
block_6:
    return -1;
block_7:
    return temp_5 < temp_4;
}
