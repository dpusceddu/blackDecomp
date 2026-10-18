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

void func_00328140(void *arg0, void *arg1) {
    if (M2C_FIELD(arg0, void **, 0x38) != NULL) {
        *M2C_FIELD(arg0, s32 **, 0x30) = 1;
    }
    if (arg1 != NULL) {
        M2C_FIELD(arg0, s32 *, 0xBC) = (s32) (((s32) M2C_FIELD(arg1, s32 *, 0x54) >> 1) & 1);
    }
    M2C_FIELD(arg0, void **, 0x38) = arg1;
    M2C_FIELD(arg0, u16 *, 0x5C) = (u16) (M2C_FIELD(arg0, u16 *, 0x5C) | 0x40);
}

void func_00328180(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, u16 *, 0x5C) = (u16) (M2C_FIELD(arg0, u16 *, 0x5C) | 4);
    M2C_FIELD(arg0, f32 *, 0xA4) = (f32) ((fparg0 * 0.5f) + 0.5f);
}
