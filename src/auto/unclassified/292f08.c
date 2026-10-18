#include "auto/prelude.h"

u8 * func_00292F08(u8 *arg0, s32 *arg1) {
    s32 var_6;
    s32 var_7;
    u8 *var_4;
    u8 temp_3;
    u8 temp_3_2;

    temp_3 = *arg0;
    var_7 = 0;
    var_4 = arg0 + 1;
    var_6 = temp_3 & 0x7F;
    if (temp_3 & 0x80) {
        do {
            temp_3_2 = *var_4;
            var_7 += 7;
            var_4 += 1;
            var_6 |= (temp_3_2 & 0x7F) << var_7;
        } while (temp_3_2 & 0x80);
    }
    *arg1 = var_6;
    return var_4;
}

u8 * func_00292F50(u8 *arg0, s32 *arg1) {
    s32 var_8;
    u32 var_7;
    u8 *var_4;
    u8 temp_6;

    var_4 = arg0;
    var_7 = 0;
    var_8 = 0;
    do {
        temp_6 = *var_4;
        var_4 += 1;
        var_8 |= (temp_6 & 0x7F) << var_7;
        var_7 += 7;
    } while (temp_6 & 0x80);
    if ((var_7 < 0x20U) && (temp_6 & 0x40)) {
        var_8 |= -1 << var_7;
    }
    *arg1 = var_8;
    return var_4;
}
