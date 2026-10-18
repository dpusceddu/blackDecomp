#include "auto/prelude.h"

extern s32 func_00343BC0(s32, f32, f32, f32);

s32 func_0034FE10(void **arg0, s32 arg1) {
    f32 temp_f12;
    void *temp_4;

    temp_4 = *arg0;
    if (temp_4 != NULL) {
        temp_f12 = M2C_FIELD(temp_4, f32 *, 0x60);
        if (temp_f12 != 1.0f) {
            func_00343BC0(arg1, temp_f12, temp_f12, temp_f12);
        }
    }
    return arg1;
}
