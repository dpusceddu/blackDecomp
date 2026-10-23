#include "auto/prelude.h"

void * func_00323B68(void *arg0, s32 arg1, void *arg2) {
    u32 temp_3;
    u32 var_5;
    void *temp_7;

    temp_7 = M2C_FIELD(arg0, void **, 0x20);
    temp_3 = M2C_FIELD(temp_7, u32 *, 0xAC);
    var_5 = 0;
    if (temp_3 != 1) {
        var_5 = M2C_FIELD(arg2, u32 *, 8);
    }
    if (var_5 < temp_3) {
        M2C_FIELD(arg2, s32 *, 0) = (s32) (M2C_FIELD(temp_7, s32 *, 0xA8) + (var_5 * 0x130) + 0x60);
    } else {
        M2C_FIELD(arg2, s32 *, 0) = 0;
    }
    return arg0;
}
