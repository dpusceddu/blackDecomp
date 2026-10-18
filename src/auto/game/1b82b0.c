#include "auto/prelude.h"

u8 * func_001B82B0(u8 *arg0) {
    s32 temp_3;
    u8 *var_4;

    var_4 = arg0;
    temp_3 = var_4 + 0x440;
loop_1:
    if (*var_4 != 0) {
        var_4 += 0x88;
        if ((s32) var_4 >= temp_3) {
            return NULL;
        }
        goto loop_1;
    }
    return var_4;
}
