#include "auto/prelude.h"

extern s32 func_0026F7E0(s32, M2C_UNK, M2C_UNK);

s32 func_0010B160(s32 arg0) {
    s32 temp_16;
    s32 var_3;

    temp_16 = arg0 + 0x9B0;
    var_3 = func_0026F7E0(temp_16, 0, 0);
    if ((var_3 != 0) && (var_3 != 0xD)) {
        var_3 = func_0026F7E0(temp_16, 1, 0);
    }
    return var_3;
}
