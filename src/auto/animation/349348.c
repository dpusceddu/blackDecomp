#include "auto/prelude.h"

extern s32 func_00348E30();
extern void func_00349278(s32 *arg0);

s32 func_00349348(void) {
    s32 *temp_2;
    s32 var_16;

    var_16 = -1;
    temp_2 = func_00348E30();
    if (temp_2 != NULL) {
        var_16 = M2C_FIELD(temp_2, s32 *, 0x10);
    }
    return var_16;
}

void func_00349378(void) {
    s32 *temp_2;

    temp_2 = func_00348E30();
    if (temp_2 != NULL) {
        func_00349278(temp_2);
    }
}

s32 func_003493A8(void) {
    s32 *temp_2;
    s32 var_16;

    var_16 = 0;
    temp_2 = func_00348E30();
    if (temp_2 != NULL) {
        var_16 = 1;
        *temp_2 |= 0x10000000;
    }
    return var_16;
}
