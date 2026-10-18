#include "auto/prelude.h"

s8 * func_002D0890(s8 *arg0, s8 arg1) {
    s8 *var_4;
    s8 *var_6;
    s8 *var_7;
    s8 temp_3;

    var_4 = arg0;
    var_7 = NULL;
    var_6 = var_4;
    do {
        temp_3 = *var_6;
        var_6 += 1;
        var_7 = ((temp_3 ^ arg1) == 0) ? var_4 : var_7;
        var_4 += 1;
    } while (temp_3 != 0);
    return var_7;
}
