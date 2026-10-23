#include "auto/prelude.h"

extern s32 func_00352A30();
extern s32 func_00343470();

s32 func_00345F28(s32 arg0, void *arg1, s32 *arg2) {
    s32 temp_2;

    if (arg1 != NULL) {
        if (M2C_FIELD(arg1, void **, 4) != NULL) {
            temp_2 = func_00352A30();
            if (func_00343470(M2C_FIELD(arg1, void **, 4), temp_2) != 0) {
                *arg2 = temp_2;
                return 1;
            }
            goto block_4;
        }
        /* Duplicate return node #5. Try simplifying control flow for better match */
        return 0;
    }
block_4:
    return 0;
}
