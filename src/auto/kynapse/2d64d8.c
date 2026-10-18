#include "auto/prelude.h"

s32 func_002D64D8(s32 arg0) {
    u32 temp_6;
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 0x38);
    if (temp_5 != NULL) {
        goto block_2;
    }
    goto block_7;
block_2:
    temp_6 = M2C_FIELD(arg0, u32 *, 0x3C);
    if (temp_6 < (u32) M2C_FIELD(temp_5, u32 *, 8)) {
        goto block_5;
    }
    goto block_7;
block_5:
    return M2C_FIELD(temp_5, s32 *, 4) + (temp_6 * 0x58) + 4;
block_7:
    return M2C_FIELD(M2C_FIELD(arg0, void **, 8), s32 *, 0x14) + 0x30;
}
