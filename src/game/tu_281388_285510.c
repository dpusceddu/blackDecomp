#include "auto/prelude.h"

s32 func_00285510(s32 arg0) {
    s32 var_3;
    s32 var_5;
    void *var_4;

    var_4 = arg0 + 0xE00;
    var_5 = 0;
    var_3 = 0;
    do {
        if (M2C_FIELD(var_4, u8 *, 0x35) != 0) {
            var_5 |= 1 << var_3;
        }
        var_3 += 1;
        var_4 += 0x3C;
    } while (var_3 < 0x18);
    return var_5;
}
