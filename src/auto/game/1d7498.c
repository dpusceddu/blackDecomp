#include "auto/prelude.h"

void func_001D7498(s32 arg0, s32 arg1) {
    s32 var_3;
    void *var_4;

    var_4 = arg0 + 0x2F;
    var_3 = 0;
loop_1:
    var_3 += 1;
    if (M2C_FIELD(var_4, s32 *, -0xF) == arg1) {
        M2C_FIELD(var_4, s8 *, 0) = 0;
        return;
    }
    var_4 += 0x10;
    if (var_3 >= 2) {
        return;
    }
    goto loop_1;
}
