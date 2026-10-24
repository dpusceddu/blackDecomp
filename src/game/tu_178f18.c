/* Translation unit tu_178f18 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

s32 func_00178F18(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4) == 0;
}

/* Assembly between the functions: func_00178F28 (40 bytes), func_00178F50 (120 bytes) */

s32 func_00178FC8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4) == 3;
}

s32 func_00178FD8(void *arg0) {
    s32 temp_3;
    s32 var_4;

    temp_3 = M2C_FIELD(arg0, s32 *, 4);
    var_4 = 0;
    if ((temp_3 == 0) || (temp_3 == 3)) {
        var_4 = 1;
    }
    return var_4;
}

s32 func_00179000(s32 *arg0) {
    return 1 << *arg0;
}

void func_00179010(void) {

}

/* Assembly between the functions: func_00179018 (56 bytes) */

void func_00179050(void) {

}

s32 func_00179058(void) {
    return 1;
}

/* Assembly between the functions: func_00179060 (112 bytes), func_001790D0 (112 bytes), func_00179140 (152 bytes), func_001791D8 (96 bytes) */

s32 func_00179238(s32 *arg0, s32 arg1) {
    s32 temp_3;

    temp_3 = 1 << arg1;
    return (temp_3 & *arg0) == temp_3;
}

void * func_00179258(void *arg0, void *arg1) {
    return arg0 + (((s32) arg1 * 0xC) + 4);
}

/* Assembly between the functions: func_00179270 (56 bytes), func_001792A8 (8 bytes) */

s32 func_001792B0(s32 arg0, s32 arg1) {
    s32 var_3;
    void *var_4;

    var_4 = arg0 + 0xC;
    var_3 = 0;
loop_1:
    if (M2C_FIELD(var_4, s32 *, -4) == 0) {
        goto block_3;
    }
    var_3 += 1;
    goto block_8;
block_3:
    if (M2C_FIELD(var_4, s32 *, 0) == arg1) {
        goto block_6;
    }
    var_3 += 1;
    goto block_8;
block_6:
    return var_3;
block_8:
    var_4 += 0xC;
    if (var_3 < 0x20) {
        goto loop_1;
    }
    return -1;
}
