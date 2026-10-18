#include "auto/prelude.h"

s32 func_00143648(s32 arg0, s32 arg1) {
    s32 temp_6;
    s32 var_4;
    void *temp_2;
    void *var_3;

    temp_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 4), void **, 0x20);
    temp_6 = M2C_FIELD(temp_2, s32 *, 8);
    var_4 = 0;
    if (temp_6 <= 0) {
        goto block_5;
    }
    var_3 = M2C_FIELD(temp_2, void **, 0xC);
loop_2:
    var_4 += 1;
    if (M2C_FIELD(var_3, s64 *, 0) != arg1) {
        goto block_4;
    }
    return M2C_FIELD(var_3, s32 *, 8);
block_4:
    var_3 += 0x10;
    if (var_4 < temp_6) {
        goto loop_2;
    }
block_5:
    return 0;
}
