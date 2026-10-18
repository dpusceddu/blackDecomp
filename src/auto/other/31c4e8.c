#include "auto/prelude.h"

extern s32 * func_0031DEB8();
extern M2C_UNK D_0040A260;

s32 func_0031C4E8(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 (*temp_2)(s32, s32, s32, s32);
    s32 temp_2_2;
    s32 var_17;

    var_17 = 0;
    if (arg0 == func_0031DEB8(NULL, &D_0040A260, 0)) {
        var_17 = M2C_FIELD(arg1, s32 *, 8);
    }
    temp_2 = M2C_FIELD(arg1, s32 (**)(s32, s32, s32, s32), 0);
    if (temp_2 != NULL) {
        temp_2_2 = temp_2(arg0, M2C_FIELD(arg1, s32 *, 4), arg2, arg3);
        var_17 = (temp_2_2 != 0) ? temp_2_2 : var_17;
    }
    return var_17;
}
