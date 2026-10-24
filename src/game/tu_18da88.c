#include "ps2/prelude.h"

f32 func_0018DA88(void *arg0) {
    f32 var_f0;

    var_f0 = 4.5f;
    if (M2C_FIELD(arg0, s32 *, 4) != 0x2A) {
        var_f0 = 2.8f;
    }
    return var_f0;
}

f32 func_0018DAB8(void *arg0) {
    f32 var_f0;

    var_f0 = 0.66f;
    if (M2C_FIELD(arg0, s32 *, 4) != 0x28) {
        var_f0 = 1.0f;
    }
    return var_f0;
}

f32 func_0018DAE8(void) {
    return 3.0f;
}

s32 func_0018DAF8(void *arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 4);
    if ((temp_3 == 0x2A) || (temp_3 == 0x26)) {
        return 0;
    }
    return 1;
}

f32 func_0018DB20(void *arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 4);
    if ((temp_3 == 0x26) || (temp_3 == 0x29)) {
        return 3.0f;
    }
    return 10.0f;
}
