#include "auto/prelude.h"

s32 func_00328108(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;
    s32 temp_2_2;
    void *temp_3;
    void *temp_4;

    if (arg1 == 0) {
        temp_4 = M2C_FIELD(arg0, void **, 0x30);
        temp_2_2 = M2C_FIELD(temp_4, s32 *, 0x1C) & 0xFFFFFFFE;
        M2C_FIELD(temp_4, s32 *, 0x1C) = temp_2_2;
        return temp_2_2;
    }
    temp_3 = M2C_FIELD(arg0, void **, 0x30);
    temp_2 = M2C_FIELD(temp_3, s32 *, 0x1C) | 1;
    M2C_FIELD(temp_3, s32 *, 0x1C) = temp_2;
    return temp_2;
}
