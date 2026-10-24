#include "ps2/prelude.h"

extern s32 func_00122D10();
extern M2C_UNK D_0048F4E0;
extern s32 * func_00123C90();

s32 func_00123B80(s32 arg0, s32 arg1) {
    s32 temp_4;
    s32 var_2;

    var_2 = 1 << arg1;
    temp_4 = M2C_FIELD(arg0, s32 *, 0x404);
    if (!(temp_4 & var_2)) {
        M2C_FIELD(arg0, s32 *, 0x404) = (s32) (temp_4 | var_2);
        var_2 = func_00122D10((s32) &D_0048F4E0, arg1);
    }
    return var_2;
}

s32 func_00123BC8(void) {
    return 0;
}

u8 func_00123BD0(void) {
    return M2C_FIELD(func_00123C90(), u8 *, 0x1A);
}
