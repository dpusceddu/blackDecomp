#include "ps2/prelude.h"

s32 func_001B1138(void *arg0) {
    s32 var_3;

    var_3 = 1;
    if (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 8) > 3.1535e7f)) {
        var_3 = 0;
    }
    return var_3;
}
