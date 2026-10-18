#include "auto/prelude.h"

s32 func_001B23C0(s32 arg0, s32 arg1) {
    s32 temp_4;
    s32 var_6;
    void *temp_2;
    void *var_3;

    temp_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x873F0), void **, 8);
    temp_4 = M2C_FIELD(temp_2, s32 *, 8);
    var_6 = 0;
    if (temp_4 <= 0) {
        goto block_5;
    }
    var_3 = M2C_FIELD(temp_2, void **, 0xC);
loop_2:
    var_6 += 1;
    if (M2C_FIELD(var_3, s64 *, 0) != arg1) {
        goto block_4;
    }
    return M2C_FIELD(var_3, s32 *, 8);
block_4:
    var_3 += 0x10;
    if (var_6 < temp_4) {
        goto loop_2;
    }
block_5:
    return 0;
}
