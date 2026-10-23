#include "auto/prelude.h"

extern s32 func_00348E30();

s32 func_00349220(void) {
    s32 *temp_2;
    s32 var_16;

    var_16 = 0;
    temp_2 = func_00348E30();
    if (M2C_FIELD(temp_2, f32 *, 0x1C) <= 1.0f) {
        var_16 = 1;
    }
    return !(M2C_FIELD(temp_2, s32 *, 0) & 0x02000001) ? var_16 : 1;
}

void func_00349278(s32 *arg0) {
    M2C_FIELD(arg0, s32 *, 0x9A0) = 0;
    M2C_FIELD(arg0, s32 *, 0x99C) = -1;
}
