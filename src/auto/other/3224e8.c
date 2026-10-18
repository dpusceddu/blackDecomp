#include "auto/prelude.h"

extern s32 func_003228D0();
extern s32 func_00322A00();

s32 func_003224E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_lo;
    s32 var_2;
    s32 var_3;

    temp_lo = (s32) (arg1 >> 1) / (s8) arg3;
    var_3 = 0;
    if ((s8) arg3 == 1) {
        var_2 = func_003228D0(arg0, arg2, temp_lo);
        goto block_4;
    }
    if ((s8) arg3 == 2) {
        var_2 = func_00322A00(arg0, arg2, temp_lo);
block_4:
        var_3 = var_2;
    }
    return var_3;
}
