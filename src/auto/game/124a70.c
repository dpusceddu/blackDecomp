#include "auto/prelude.h"

extern f32 func_0026BB98();
extern s32 func_0026BBC0();

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
