#include "auto/prelude.h"

extern void * D_0040F4D0;

s32 func_001735E0(f32 *arg0) {
    s32 var_2;

    var_2 = 1;
    if (*arg0 == -1.0f) {
        var_2 = 0;
    }
    return var_2;
}

s32 func_00173610(f32 *arg0) {
    s32 var_2;

    var_2 = 1;
    if (!(*arg0 <= M2C_FIELD(D_0040F4D0, f32 *, 0x20))) {
        var_2 = 0;
    }
    return var_2;
}

void func_00173640(f32 *arg0, f32 fparg0) {
    *arg0 = M2C_FIELD(D_0040F4D0, f32 *, 0x20) + fparg0;
}
