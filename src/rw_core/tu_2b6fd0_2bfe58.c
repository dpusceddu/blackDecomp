/* Translation unit renderware_core/tu_2b6fd0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern M2C_UNK D_003C3D80;
extern M2C_UNK D_0044E750;

M2C_UNK * func_002BFE58(void) {
    return &D_003C3D80;
}

/* Assembly between the functions: func_002BFE68 (88 bytes) */

M2C_UNK * func_002BFEC0(void) {
    return &D_0044E750;
}

s32 func_002BFED0(s32 arg0) {
    s32 var_2;
    s32 var_4;

    var_4 = arg0;
    var_2 = -1;
    if (var_4 != 0) {
        do {
            var_4 = (s32) ((u32) var_4 >> 1);
            var_2 += 1;
        } while (var_4 != 0);
    }
    return var_2;
}

/* Assembly between the functions: func_002BFF00 (16 bytes), func_002BFF10 (64 bytes), func_002BFF50 (32 bytes), func_002BFF70 (16 bytes), func_002BFF80 (8 bytes), func_002BFF88 (176 bytes), func_002C0038 (184 bytes), func_002C00F0 (120 bytes), func_002C0168 (88 bytes) */

s32 func_002C01C0(s32 *arg0) {
    s32 var_3;

    var_3 = 0;
    if (arg0 != NULL) {
        var_3 = (*arg0 == 0) ? 0 : 4;
    }
    return var_3;
}
