#include "auto/prelude.h"

extern f32 func_001378F0();

void func_00138470(void *arg0, void *arg1) {
    f32 var_f1;

    var_f1 = 0.0f;
    M2C_FIELD(arg0, void **, 0) = arg1;
    if (M2C_FIELD(arg1, f32 *, 0x308) > 0.0f) {
        var_f1 = 1.0f / func_001378F0(arg1);
    }
    M2C_FIELD(arg0, f32 *, 4) = var_f1;
}
