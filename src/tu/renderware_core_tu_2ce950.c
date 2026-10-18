/* Translation unit renderware_core/tu_2ce950 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

s32 func_002CF5C0(void) {
    return 1;
}

s32 func_002CF5C8(void) {
    return 1;
}

void func_002CF5D0(void) {

}

void func_002CF5D8(void) {

}

/* Assembly between the functions: func_002CF5E0 (24 bytes), func_002CF5F8 (24 bytes), func_002CF610 (312 bytes), func_002CF748 (8 bytes), func_002CF750 (296 bytes), func_002CF878 (16 bytes), func_002CF888 (136 bytes), func_002CF910 (128 bytes), func_002CF990 (304 bytes), func_002CFAC0 (728 bytes), func_002CFD98 (80 bytes), func_002CFDE8 (16 bytes) ... */

void * func_002CFE90(void *arg0, s32 arg1) {
    void *var_16;

    var_16 = M2C_FIELD(arg0, void **, 0x14);
    if (var_16 != NULL) {
        do {
            M2C_FIELD(var_16, M2C_UNK (**)(s32, s32, s32), 0x24)(arg1, M2C_FIELD(var_16, s32 *, 0), M2C_FIELD(var_16, s32 *, 4));
            var_16 = M2C_FIELD(var_16, void **, 0x34);
        } while (var_16 != NULL);
    }
    return arg0;
}

/* Assembly between the functions: func_002CFEF0 (80 bytes) */

s32 func_002CFF40(s32 arg0) {
    return arg0;
}

s32 func_002CFF48(s32 arg0) {
    return arg0;
}

s32 func_002CFF50(s32 arg0) {
    return arg0;
}

/* Assembly between the functions: func_002CFF58 (88 bytes) */

s32 func_002CFFB0(void) {
    return 1;
}

/* Assembly between the functions: func_002CFFB8 (8 bytes), func_002CFFC0 (184 bytes), func_002D0078 (120 bytes), func_002D00F0 (88 bytes), func_002D0148 (48 bytes), func_002D0178 (264 bytes), func_002D0280 (1016 bytes) */

void func_002D0678(void) {

}

/* Assembly between the functions: func_002D0680 (56 bytes), func_002D06B8 (160 bytes), func_002D0758 (112 bytes) */

s8 * func_002D07C8(s8 *arg0) {
    s8 *var_3;
    s8 temp_5;

    if (arg0 != NULL) {
        var_3 = arg0;
        if (*arg0 != 0) {
            do {
                temp_5 = *var_3;
                if ((u32) (temp_5 - 0x61) < 0x1AU) {
                    *var_3 = temp_5 - 0x20;
                }
                var_3 += 1;
            } while (*var_3 != 0);
        }
    }
    return arg0;
}

s8 * func_002D0810(s8 *arg0) {
    s8 *var_3;
    s8 temp_5;

    if (arg0 != NULL) {
        var_3 = arg0;
        if (*arg0 != 0) {
            do {
                temp_5 = *var_3;
                if ((u32) (temp_5 - 0x41) < 0x1AU) {
                    *var_3 = temp_5 + 0x20;
                }
                var_3 += 1;
            } while (*var_3 != 0);
        }
    }
    return arg0;
}

/* Assembly between the functions: func_002D0858 (56 bytes) */

s8 * func_002D0890(s8 *arg0, s8 arg1) {
    s8 *var_4;
    s8 *var_6;
    s8 *var_7;
    s8 temp_3;

    var_4 = arg0;
    var_7 = NULL;
    var_6 = var_4;
    do {
        temp_3 = *var_6;
        var_6 += 1;
        var_7 = ((temp_3 ^ arg1) == 0) ? var_4 : var_7;
        var_4 += 1;
    } while (temp_3 != 0);
    return var_7;
}
