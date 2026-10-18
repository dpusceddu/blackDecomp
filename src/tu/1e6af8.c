#include "auto/prelude.h"

extern s32 func_00135550();
extern s32 func_001848C0();

s32 func_001E6AF8(s32 arg0, void *arg1) {
    s32 temp_2;

    if (((M2C_FIELD(arg1, s32 *, 0x38C) ^ 1) != 0) && (func_00135550(arg1) != 0)) {
        temp_2 = func_001848C0(func_00135550(arg1) + 0x6F0);
        return (func_001E6B70(arg0, temp_2) == 0) ? 0 : temp_2;
    }
    return 0;
}

s32 func_001E6B70(s32 arg0, void *arg1) {
    s32 var_2;

    var_2 = 0;
    if (arg1 != NULL) {
        var_2 = M2C_FIELD(arg1, s32 *, 0x348) != 0;
    }
    return var_2;
}
