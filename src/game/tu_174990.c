#include "ps2/prelude.h"

s32 func_00174990(s32 arg0) {
    if (M2C_FIELD(arg0, u8 *, 9) != 0) {
        goto block_2;
    }
    goto block_4;
block_2:
block_3:
    return 0;
block_4:
    if ((u8) M2C_FIELD(arg0, u8 *, 8) < (u8) M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0x35)) {
        goto block_3;
    }
    M2C_FIELD(arg0, u8 *, 9) = 1U;
    return 1;
}
