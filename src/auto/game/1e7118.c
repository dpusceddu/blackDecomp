#include "auto/prelude.h"

extern void * D_0040F4D0;

s32 func_001E7118(void *arg0) {
    s32 var_5;

    var_5 = 1;
    if (!((M2C_FIELD(arg0, f32 *, 0x30) + M2C_FIELD(arg0, f32 *, 0x34)) < M2C_FIELD(D_0040F4D0, f32 *, 0x20))) {
        var_5 = 0;
    }
    return var_5;
}
