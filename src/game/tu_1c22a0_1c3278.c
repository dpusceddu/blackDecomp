#include "ps2/prelude.h"

void func_001C3278(void *arg0, s128 arg1, f32 fparg0, f32 fparg1) {
    if (M2C_FIELD(arg0, f32 *, 0x14) == fparg0) {
        if (M2C_FIELD(arg0, f32 *, 0x18) != fparg1) {
            goto block_3;
        }
    } else {
block_3:
        M2C_FIELD(arg0, s8 *, 0x20) = 1;
    }
    M2C_FIELD(arg0, f32 *, 0x18) = fparg1;
    M2C_FIELD(arg0, s128 *, 0) = arg1;
    M2C_FIELD(arg0, f32 *, 0x14) = fparg0;
}
