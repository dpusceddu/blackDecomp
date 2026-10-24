#include "ps2/prelude.h"

extern s32 (*D_003CEC68)();

s32 func_00312CC8(s32 arg0) {
    s32 temp_2;
    s32 var_2;

    temp_2 = D_003CEC68(arg0 + 0x80);
    var_2 = 0;
    if (temp_2 != 0) {
        var_2 = ((u32) (temp_2 + 0x40) >> 6) << 6;
        M2C_FIELD(var_2, s32 *, -4) = temp_2;
    }
    return var_2;
}
