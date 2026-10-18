#include "auto/prelude.h"

extern s32 func_00138320();
extern s32 func_00135570();
extern s32 func_0012D158();
extern void * D_0040F4D0;

s32 func_001E5CD8(void) {
    return 1;
}

s32 func_001E5CE0(void *arg0, s32 arg1) {
    s32 temp_2;
    s32 var_16;
    s32 var_18;

    var_16 = -1;
    var_18 = 0;
    temp_2 = func_00138320(func_00135570(arg1));
    if (temp_2 >= 0x24) {
        if (temp_2 < 0x26) {
            var_18 = M2C_FIELD(arg0, s32 *, 0x594);
            var_16 = 2;
        } else if (temp_2 < 0x2B) {
            var_18 = M2C_FIELD(arg0, s32 *, 0x590);
            var_16 = 1;
        }
    }
    return (func_0012D158(D_0040F4D0, 0, var_16 - 1) * 0x190) + var_18;
}

void func_001E5D80(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s8 *, 0x170) = 0;
}
