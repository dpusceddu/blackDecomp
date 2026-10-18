#include "auto/prelude.h"

extern s32 func_001749E8();
extern s32 func_00174C08();

s32 func_00175250(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_5;
    u8 temp_3;

    func_001749E8(arg0, 4, arg1, arg2, arg3);
    temp_5 = M2C_FIELD(arg0, s32 *, 0x28);
    M2C_FIELD(arg0, s32 *, 0x30) = arg2;
    if (temp_5 != 0) {
        temp_3 = M2C_FIELD(((M2C_FIELD(arg2, u8 *, 0x27) * 8) + M2C_FIELD(arg3, s32 *, 0x14)), u8 *, 4);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) temp_3;
        func_00174C08(arg0, temp_5, (s32) temp_3);
    }
    return 1;
}
