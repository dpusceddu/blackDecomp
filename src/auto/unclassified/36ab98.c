#include "auto/prelude.h"

extern s32 func_0036AB68();

s32 func_0036AB98(s32 arg0, s32 arg1) {
    if (arg1 < 0) {
        goto block_4;
    }
    if (arg1 >= M2C_FIELD(arg0, s32 *, 0x20)) {
        goto block_3;
    }
    goto block_5;
block_3:
block_4:
    return func_0036AB68(arg0);
block_5:
    return M2C_FIELD(arg0, s32 *, 0x1C) + (arg1 << 6);
}
