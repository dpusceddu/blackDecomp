#include "auto/prelude.h"

s8 func_00183858(void *arg0, s8 arg1) {
    s8 var_5;

    var_5 = arg1;
    if (var_5 < (M2C_FIELD(arg0, s32 *, 8) - 1)) {
        var_5 += 1;
    }
    return var_5;
}
