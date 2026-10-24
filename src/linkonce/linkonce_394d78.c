#include "ps2/prelude.h"

extern s32 D_003CE5A0;

f32 func_00394D78(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_3;

    if (arg2 < arg1) {
        var_3 = ((s32) (arg1 * (arg1 - 1)) / 2) + arg2;
    } else {
        var_3 = ((s32) (arg2 * (arg2 - 1)) / 2) + arg1;
    }
    return M2C_FIELD(((var_3 * 4) + D_003CE5A0), f32 *, 0);
}
