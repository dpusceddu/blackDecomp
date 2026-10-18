#include "auto/prelude.h"

extern s32 func_003106F0(s32, M2C_UNK, M2C_UNK, f32);

void * func_0031A3B8(void *arg0, s32 arg1, f32 *arg2) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x60);
    M2C_FIELD(arg0, f32 *, 0x78) = (f32) *arg2;
    if (temp_4 != 0) {
        func_003106F0(temp_4, 6, 1, *arg2);
    }
    return arg0;
}
