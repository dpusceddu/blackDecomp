#include "auto/prelude.h"

s32 func_0018F6A8(void *arg0) {
    s32 var_3;

    var_3 = 0;
    if ((M2C_FIELD(arg0, u8 *, 0x14) != 0) || (M2C_FIELD(arg0, u8 *, 0x15) != 0)) {
        var_3 = 1;
    }
    return var_3;
}
