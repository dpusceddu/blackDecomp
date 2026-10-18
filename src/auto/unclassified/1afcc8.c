#include "auto/prelude.h"

s32 func_001AFCC8(void) {
    return 1;
}

void func_001AFCD0(void) {

}

s32 func_001AFCD8(void *arg0, f32 fparg0) {
    f32 temp_f0;

    if (M2C_FIELD(arg0, s32 *, 4) != -1) {
        temp_f0 = M2C_FIELD(arg0, f32 *, 0) - fparg0;
        M2C_FIELD(arg0, f32 *, 0) = temp_f0;
        if (temp_f0 <= 0.0f) {
            M2C_FIELD(arg0, f32 *, 0) = 0.0f;
            return 1;
        }
    }
    return 0;
}
