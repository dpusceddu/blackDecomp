#include "auto/prelude.h"

extern s32 D_003BCAC8;
extern f32 func_0026BB98();
extern s32 func_0026BBC0();

void func_00124A58(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(((arg1 * 4) + D_003BCAC8), s32 *, 0) = arg2;
}

s32 func_00124A70(void *arg0) {
    f32 var_f20;
    s32 var_2;

    var_f20 = func_0026BB98(M2C_FIELD(arg0, s32 *, 0xC), 2);
    if (func_0026BBC0(M2C_FIELD(arg0, s32 *, 0xC), 2) == 0) {
        var_f20 = 0.0f;
    }
    var_2 = 1;
    if (!(var_f20 > 0.0f)) {
        var_2 = 0;
    }
    return var_2;
}
