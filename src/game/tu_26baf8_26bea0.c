#include "ps2/prelude.h"

void func_0026BEA0(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xE8) != 0) {
        M2C_FIELD(arg0, s32 *, 0xE8) = 0;
        M2C_FIELD(arg0, s32 *, 0xEC) = -1;
    }
}

f32 func_0026BEC0(void *arg0, f32 fparg0) {
    f32 temp_f0;
    f32 temp_f1;
    f32 var_f12;
    f32 var_f12_2;

    var_f12_2 = fparg0;
    temp_f1 = M2C_FIELD(arg0, f32 *, 0xD0);
    if (temp_f1 < var_f12_2) {
        var_f12_2 = temp_f1;
    }
    temp_f0 = M2C_FIELD(arg0, f32 *, 0xD4);
    var_f12 = var_f12_2 - temp_f0;
    if (var_f12 < 0.0f) {
        var_f12 = 0.0f;
    }
    return var_f12 * (1.0f / (temp_f1 - temp_f0));
}

f32 func_0026BF10(void *arg0, f32 fparg0) {
    f32 temp_f0;
    f32 temp_f1;
    f32 var_f12;
    f32 var_f12_2;

    var_f12_2 = fparg0;
    temp_f1 = M2C_FIELD(arg0, f32 *, 0xD8);
    if (temp_f1 < var_f12_2) {
        var_f12_2 = temp_f1;
    }
    temp_f0 = M2C_FIELD(arg0, f32 *, 0xDC);
    var_f12 = var_f12_2 - temp_f0;
    if (var_f12 < 0.0f) {
        var_f12 = 0.0f;
    }
    return var_f12 * (1.0f / (temp_f1 - temp_f0));
}
