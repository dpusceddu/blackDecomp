#include "auto/prelude.h"

s32 func_001792B0(s32 arg0, s32 arg1) {
    s32 var_3;
    void *var_4;

    var_4 = arg0 + 0xC;
    var_3 = 0;
loop_1:
    if (M2C_FIELD(var_4, s32 *, -4) == 0) {
        goto block_3;
    }
    var_3 += 1;
    goto block_8;
block_3:
    if (M2C_FIELD(var_4, s32 *, 0) == arg1) {
        goto block_6;
    }
    var_3 += 1;
    goto block_8;
block_6:
    return var_3;
block_8:
    var_4 += 0xC;
    if (var_3 < 0x20) {
        goto loop_1;
    }
    return -1;
}
