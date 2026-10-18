#include "auto/prelude.h"

extern M2C_UNK * func_00343278(s32, s32);
extern M2C_UNK D_003D1E30;

M2C_UNK * func_00345E90(s32 arg0, void *arg1) {
    M2C_UNK *var_2;
    s32 temp_4;

    if ((arg1 == NULL) || (temp_4 = M2C_FIELD(arg1, s32 *, 4), (temp_4 == 0)) || (var_2 = func_00343278(temp_4, arg0), (var_2 == NULL))) {
        var_2 = &D_003D1E30;
    }
    return var_2;
}
