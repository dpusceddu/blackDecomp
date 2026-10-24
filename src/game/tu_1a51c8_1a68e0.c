#include "ps2/prelude.h"

extern M2C_UNK D_00443350;

M2C_UNK * func_001A68E0(void *arg0, s32 arg1) {
    s32 temp_4;

    temp_4 = arg1 * 4;
    if (M2C_FIELD((M2C_FIELD(arg0, s32 *, 0x50) + temp_4), s32 *, 0x34) < 0) {
        return &D_00443350;
    }
    return M2C_FIELD((arg0 + temp_4), s32 *, 0x30) + 0x40;
}

s32 func_001A6918(void **arg0) {
    return M2C_FIELD(*arg0, s32 *, 0xC4) == 2;
}
