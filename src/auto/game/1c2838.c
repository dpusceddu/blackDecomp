#include "auto/prelude.h"

void func_001C2838(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x34);
    if (temp_3 != 9) {
        M2C_FIELD(arg0, f32 *, 0x30) = fparg2;
        M2C_FIELD(arg0, s32 *, 0x38) = temp_3;
        M2C_FIELD(arg0, s32 *, 0x34) = 2;
        M2C_FIELD(arg0, f32 *, 0x18) = 1.0f;
        M2C_FIELD(arg0, f32 *, 0x28) = fparg0;
        M2C_FIELD(arg0, f32 *, 0x2C) = fparg1;
        M2C_FIELD(arg0, s32 *, 0x14) = 0;
    }
}
