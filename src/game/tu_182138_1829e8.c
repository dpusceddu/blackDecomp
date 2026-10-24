#include "ps2/prelude.h"

s32 func_001829E8(void *arg0) {
    s32 temp_3;
    s32 var_4;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x30);
    var_4 = 0;
    if ((temp_3 == 0) || (temp_3 == 8)) {
        var_4 = 1;
    }
    return var_4;
}
