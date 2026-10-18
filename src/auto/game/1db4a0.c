#include "auto/prelude.h"

extern s32 func_001DD6C0();

s32 func_001DB4A0(s32 arg0) {
    s32 temp_3;
    s32 var_2;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x28);
    var_2 = temp_3 < 7;
    if ((temp_3 >= 0) && (var_2 == 0)) {
        var_2 = temp_3 < 0xA;
        if (var_2 != 0) {
            func_001DD6C0(M2C_FIELD(arg0, s32 *, 0));
            var_2 = 6;
            M2C_FIELD(arg0, s32 *, 0x28) = 6;
        }
    }
    return var_2;
}
