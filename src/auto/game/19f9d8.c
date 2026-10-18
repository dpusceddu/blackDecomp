#include "auto/prelude.h"

extern s32 func_0018AB08();
extern s32 func_001823B0();
extern s32 func_00182410();
extern s32 func_001829A8();
extern s32 func_001829E8();

s32 func_0019F9D8(void *arg0) {
    s32 var_2;

    if (M2C_FIELD(arg0, u8 *, 0x20) != 0) {
        M2C_FIELD(arg0, s8 *, 0x21) = 0;
        return 1;
    }
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 0x694), s8 *, 0x30) = 0;
    if (func_0018AB08(M2C_FIELD(arg0, void **, 0) + 0x150) != 0) {
        var_2 = func_001823B0(M2C_FIELD(arg0, void **, 0) + 0x810, M2C_FIELD(arg0, s128 *, 0x10), 0);
    } else {
        var_2 = func_00182410(M2C_FIELD(arg0, void **, 0) + 0x810, M2C_FIELD(arg0, s128 *, 0x10), 0, 0);
    }
    if ((var_2 == 0) || (func_001829A8(M2C_FIELD(arg0, void **, 0) + 0x810) == 0) || (func_001829E8(M2C_FIELD(arg0, void **, 0) + 0x810) != 0)) {
        M2C_FIELD(arg0, u8 *, 0x20) = 1U;
        return 1;
    }
    return 0;
}
