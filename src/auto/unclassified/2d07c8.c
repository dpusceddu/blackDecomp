#include "auto/prelude.h"

s8 * func_002D07C8(s8 *arg0) {
    s8 *var_3;
    s8 temp_5;

    if (arg0 != NULL) {
        var_3 = arg0;
        if (*arg0 != 0) {
            do {
                temp_5 = *var_3;
                if ((u32) (temp_5 - 0x61) < 0x1AU) {
                    *var_3 = temp_5 - 0x20;
                }
                var_3 += 1;
            } while (*var_3 != 0);
        }
    }
    return arg0;
}

s8 * func_002D0810(s8 *arg0) {
    s8 *var_3;
    s8 temp_5;

    if (arg0 != NULL) {
        var_3 = arg0;
        if (*arg0 != 0) {
            do {
                temp_5 = *var_3;
                if ((u32) (temp_5 - 0x41) < 0x1AU) {
                    *var_3 = temp_5 + 0x20;
                }
                var_3 += 1;
            } while (*var_3 != 0);
        }
    }
    return arg0;
}
