#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00140AB0(s32);

void func_0013C950(void *arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x32C);
    if (temp_2 == (arg0 + 0x4F0)) {
        func_00140AB0(temp_2);
    }
}

f32 func_0013C980(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x32C) == (arg0 + 0x4F0)) {
        return fabsf(M2C_FIELD(arg0, f32 *, 0x580)) + fabsf(M2C_FIELD(arg0, f32 *, 0x584));
    }
    return 0.0f;
}
