#include "auto/prelude.h"

s32 func_00175C30(void *arg0) {
    s32 var_3;
    u8 *var_4;

    var_4 = arg0 + 0x40;
    var_3 = 0;
loop_1:
    if (*var_4 != 0) {
        var_3 += 1;
        var_4 += 0xC;
        if (var_3 >= 0x30) {
            return -1;
        }
        goto loop_1;
    }
    return var_3;
}
