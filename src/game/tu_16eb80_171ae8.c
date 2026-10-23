#include "auto/prelude.h"

extern s32 func_002E41D8();
extern M2C_UNK D_003DD078;
extern M2C_UNK D_004514F8;

s32 func_00171AE8(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_3;
    void *temp_6;
    void *temp_7;

    func_002E41D8(arg0, arg1, arg2);
    M2C_FIELD(arg0, s32 *, 0x54) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003DD078;
    temp_3 = arg0 + 0x30;
    temp_6 = arg0 + 0x3C;
    temp_7 = arg0 + 0x48;
    M2C_FIELD(arg0, f32 *, 0x30) = (f32) M2C_FIELD(&D_004514F8, f32 *, 0);
    M2C_FIELD(temp_3, f32 *, 4) = (f32) M2C_FIELD(&D_004514F8, f32 *, 4);
    M2C_FIELD(temp_3, f32 *, 8) = (f32) M2C_FIELD(&D_004514F8, f32 *, 8);
    M2C_FIELD(arg0, f32 *, 0x3C) = (f32) M2C_FIELD(&D_004514F8, f32 *, 0);
    M2C_FIELD(temp_6, f32 *, 4) = (f32) M2C_FIELD(&D_004514F8, f32 *, 4);
    M2C_FIELD(temp_6, f32 *, 8) = (f32) M2C_FIELD(&D_004514F8, f32 *, 8);
    M2C_FIELD(arg0, f32 *, 0x48) = (f32) M2C_FIELD(&D_004514F8, f32 *, 0);
    M2C_FIELD(temp_7, f32 *, 4) = (f32) M2C_FIELD(&D_004514F8, f32 *, 4);
    M2C_FIELD(temp_7, f32 *, 8) = (f32) M2C_FIELD(&D_004514F8, f32 *, 8);
    return arg0;
}
