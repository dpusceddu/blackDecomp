#include "auto/prelude.h"

extern s32 func_00125C60();

s32 func_0014B878(void) {
    return 5;
}

void func_0014B880(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x110) = (f32) (M2C_FIELD(arg0, f32 *, 0x110) + 2.0f);
}

void func_0014B8A0(void *arg0) {
    void *temp_3;

    func_00125C60();
    temp_3 = M2C_FIELD(arg0, void **, 0x10);
    M2C_FIELD(arg0, s32 *, 0xC4) = M2C_FIELD(temp_3, s32 (**)(void *), 0x94)(arg0 + M2C_FIELD(temp_3, s16 *, 0x90));
    M2C_FIELD(arg0, s32 *, 0xD8) = 0;
}
