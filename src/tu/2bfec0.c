#include "auto/prelude.h"

extern M2C_UNK D_0044E750;

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
