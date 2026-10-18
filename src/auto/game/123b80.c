#include "auto/prelude.h"

extern s32 func_00122D10();
extern M2C_UNK D_0048F4E0;

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
