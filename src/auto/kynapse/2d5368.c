#include "auto/prelude.h"

s32 func_002D5368(s32 arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x54) != 0) {
        goto block_2;
    }
    goto block_7;
block_2:
    if (M2C_FIELD(arg0, u8 *, 0x55) != 0) {
        goto block_5;
    }
    goto block_7;
block_5:
    return arg0 + 0x14;
block_7:
    return M2C_FIELD(M2C_FIELD(arg0, void **, 8), s32 *, 0x14) + 0x30;
}
