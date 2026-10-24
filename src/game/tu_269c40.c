#include "ps2/prelude.h"

extern s32 func_0036C5D8();

s32 func_00269C40(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_4;

    M2C_FIELD(arg0, s32 *, 0x18) = 1;
    var_4 = func_0036C5D8(M2C_FIELD(arg0, s32 *, 0x30), arg1 & 0x0FFFFFFF, arg2);
    if (M2C_FIELD(arg0, s32 *, 0x20) != 0) {
        M2C_FIELD(arg0, s32 *, 0x18) = 2;
        var_4 = (var_4 >= 0) ? arg2 : 0;
    }
    if (var_4 > 0) {
        M2C_FIELD(arg0, s64 *, 0x10) = (s64) (var_4 + M2C_FIELD(arg0, s64 *, 0x10));
        return var_4;
    }
    return 0;
}
