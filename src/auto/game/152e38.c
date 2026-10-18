#include "auto/prelude.h"

extern void * func_001AFD80();

f32 func_00152E38(void *arg0) {
    f32 var_f0;
    void *temp_2;

    temp_2 = func_001AFD80(arg0 + 0x1A0, M2C_FIELD(arg0, s32 *, 0x118));
    var_f0 = 15.0f;
    if ((temp_2 != NULL) && (M2C_FIELD(temp_2, s32 *, 0x54) == 8)) {
        var_f0 = 3.5f;
    }
    return var_f0;
}
