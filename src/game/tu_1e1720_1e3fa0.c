#include "ps2/prelude.h"

extern s32 func_001E36A0();

s32 func_001E3FA0(s32 arg0, s32 arg1) {
    s32 var_17;
    s32 var_2;
    void *var_16;

    var_16 = arg0 + 0x250;
    var_17 = 3;
    do {
        var_2 = M2C_FIELD(var_16, s32 *, 0x28);
        if (var_2 == arg1) {
            var_2 = func_001E36A0((s32) var_16);
        }
        var_17 -= 1;
        var_16 += 0x30;
    } while (var_17 >= 0);
    return var_2;
}
