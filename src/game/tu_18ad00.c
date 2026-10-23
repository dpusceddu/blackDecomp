#include "auto/prelude.h"

extern s32 func_00164238(s32);
extern s32 func_001640D0(s32, s32);

void func_0018AD00(void *arg0) {
    s32 temp_5;

    temp_5 = M2C_FIELD(arg0, s32 *, 4);
    if ((temp_5 != 0) && (M2C_FIELD(arg0, u8 *, 8) != 0)) {
        M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 0x7C), void **, 0x330), s32 *, 0xCC) = (s32) (temp_5 + 0x5C);
    }
}

s32 func_0018AD30(void *arg0) {
    s32 temp_4;
    s32 var_2;

    temp_4 = M2C_FIELD(arg0, s32 *, 4);
    var_2 = 0;
    if (temp_4 != 0) {
        var_2 = func_00164238(temp_4) != 0;
    }
    return var_2;
}

void func_0018AD60(void *arg0) {
    func_001640D0(M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 0));
}

void func_0018AD80(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x44) = arg1;
}
