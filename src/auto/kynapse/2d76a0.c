#include "auto/prelude.h"

extern M2C_UNK D_004514F8;
extern s32 func_002E1C58();
extern M2C_UNK D_004512B0;
extern s32 func_002E0018();

s32 func_002D76A0(void *arg0, s32 arg1) {
    s32 temp_2;
    void *temp_3;
    void *temp_4;

    temp_4 = arg0 + 0x10;
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) M2C_FIELD(&D_004514F8, f32 *, 0);
    M2C_FIELD(temp_4, f32 *, 4) = (f32) M2C_FIELD(&D_004514F8, f32 *, 4);
    M2C_FIELD(temp_4, f32 *, 8) = (f32) M2C_FIELD(&D_004514F8, f32 *, 8);
    M2C_FIELD(arg0, s8 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0x7FFFFFFF;
    temp_2 = func_002E1C58(M2C_FIELD(arg0, void **, 8), &D_004512B0);
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x24) = temp_2;
    if (func_002E0018(arg0, arg1) == 0) {
        return 0;
    }
    temp_3 = M2C_FIELD(arg0, void **, 0);
    return M2C_FIELD(temp_3, s32 (**)(void *), 0x44)(arg0 + M2C_FIELD(temp_3, s16 *, 0x40)) != 0;
}
