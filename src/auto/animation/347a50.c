#include "auto/prelude.h"

s32 func_00347A50(void *arg0) {
    s32 var_5;

    var_5 = 0;
    if (M2C_FIELD(arg0, f32 *, 0x1C) <= 1.0f) {
        var_5 = 1;
    }
    return !(M2C_FIELD(arg0, s32 *, 0) & 0x02000001) ? var_5 : 1;
}
