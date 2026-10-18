#include "auto/prelude.h"

extern s32 func_002D9880();

void func_002D9970(void *arg0, f32 fparg0) {
    f32 var_f0;

    var_f0 = 0.0f;
    if (fparg0 < 0.0f) {
        /* Duplicate return node #1. Try simplifying control flow for better match */
        M2C_FIELD(arg0, f32 *, 8) = var_f0;
        return;
    }
    var_f0 = 360.0f;
    if (!(fparg0 > 360.0f)) {
        M2C_FIELD(arg0, f32 *, 8) = fparg0;
        return;
    }
    M2C_FIELD(arg0, f32 *, 8) = var_f0;
}

void func_002D99B8(void) {
    func_002D9880(1, 0xFFFF);
}

void func_002D99D8(void) {
    func_002D9880(0, 0xFFFF);
}
