#include "auto/prelude.h"

s32 func_0016FB18(s32 arg0, s32 arg1) {
    if (arg1 == 1) {
        goto block_3;
    }
    if (arg1 != 2) {
        goto block_4;
    }
    return arg0 + 0x88;
block_3:
    return arg0 + 0x7C;
block_4:
    return 0;
}
