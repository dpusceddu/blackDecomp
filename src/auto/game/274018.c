#include "auto/prelude.h"

s32 func_00274018(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_2;

    var_2 = arg1 + 8;
    if (arg2 != 0) {
        var_2 = ((var_2 + arg2) - 1) & -arg2;
    }
    return (var_2 * arg0) + arg2;
}
