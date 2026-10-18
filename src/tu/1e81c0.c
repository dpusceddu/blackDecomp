#include "auto/prelude.h"

extern s32 func_001EFD30();
extern void * D_0040F510;

s32 func_001E81C0(void *arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x1AC);
    if (temp_3 != 1) {
        if (temp_3 < 2) {
            if (temp_3 != 0) {
                return 0;
            }
            goto block_6;
        }
        if (temp_3 != 2) {
            if (temp_3 == 3) {
block_6:
                M2C_FIELD(arg0, s32 *, 0x1AC) = 1;
                goto block_7;
            }
            /* Duplicate return node #11. Try simplifying control flow for better match */
            return 0;
        }
        goto block_9;
    }
block_7:
    if (func_001EFD30(D_0040F510) != 0) {
        M2C_FIELD(arg0, s32 *, 0x1AC) = 2;
block_9:
        return 1;
    }
    return 0;
}

s32 func_001E8248(void) {
    return 1;
}
