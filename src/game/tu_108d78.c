#include "auto/prelude.h"

void func_00108D78(void *arg0) {
    s32 var_5;
    void *var_3;

    var_5 = 0;
    var_3 = arg0;
    do {
        M2C_FIELD(var_3, s32 *, 0x10) = var_5;
        M2C_FIELD(var_3, s8 *, 0x138) = 0;
        var_5 += 1;
        M2C_FIELD(var_3, s8 *, 0x139) = 0;
        M2C_FIELD(var_3, s8 *, 0x13A) = 0;
        M2C_FIELD(var_3, s8 *, 0x13B) = 0;
        M2C_FIELD(var_3, s32 *, 0) = 0;
        M2C_FIELD(var_3, s32 *, 4) = 0;
        var_3 += 0x140;
    } while (var_5 < 0xA);
    M2C_FIELD(arg0, s32 *, 0xC84) = 1;
}
