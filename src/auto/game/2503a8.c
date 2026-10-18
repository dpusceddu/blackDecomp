#include "auto/prelude.h"

extern s32 * func_00248C78();
extern s32 D_003BFAB8;
extern s32 D_003BFABC;

s32 * func_002503A8(s32 arg0, s32 arg1, u16 **arg2) {
    s32 *temp_2;

    temp_2 = func_00248C78(D_003BFAB8 + 8, arg2);
    if ((temp_2 != NULL) && (((((s32) *temp_2 >> 4) & 1) ^ 1) == 0)) {
        return temp_2;
    }
    return func_00248C78(D_003BFABC + 8, arg2);
}
