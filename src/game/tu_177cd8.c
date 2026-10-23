#include "auto/prelude.h"

s32 func_00177CD8(s32 arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x24);
    if (temp_2 == 0) {
        goto block_4;
    }
    if (temp_2 < 0) {
        goto block_5;
    }
    if (temp_2 >= 5) {
        goto block_5;
    }
    return 1;
block_4:
    return 0;
block_5:
    return 0;
}
