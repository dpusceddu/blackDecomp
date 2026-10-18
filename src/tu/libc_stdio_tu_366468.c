/* Translation unit libc_stdio/tu_366468 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_00366468();

void func_00366510(void *arg0, void *arg1) {
    s32 temp_4;

    if (arg1 != NULL) {
        temp_4 = M2C_FIELD(arg1, s32 *, 4) * 4;
        M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD((temp_4 + M2C_FIELD(arg0, s32 *, 0x4C)), s32 *, 0);
        M2C_FIELD((temp_4 + M2C_FIELD(arg0, s32 *, 0x4C)), u32 *, 0) = arg1;
    }
}

/* Assembly between the functions: func_00366548 (264 bytes), func_00366650 (312 bytes), func_00366788 (136 bytes), func_00366810 (192 bytes) */

s32 func_003668D0(s32 arg0, s32 arg1) {
    void *temp_2;

    temp_2 = func_00366468(arg0, 1);
    M2C_FIELD(temp_2, s32 *, 0x14) = arg1;
    M2C_FIELD(temp_2, s32 *, 0x10) = 1;
    return (s32) temp_2;
}
