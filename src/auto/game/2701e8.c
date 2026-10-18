#include "auto/prelude.h"

void func_002701E8(void *arg0) {
    s32 temp_2;
    s32 temp_6;
    u32 temp_5;

    temp_6 = M2C_FIELD(arg0, s32 *, 0x2F0);
    M2C_FIELD(arg0, s32 *, 0x2E0) = temp_6;
    temp_5 = 0x100000 - (temp_6 + M2C_FIELD(arg0, s32 *, 0x300));
    M2C_FIELD(arg0, u32 *, 0x2EC) = temp_5;
    temp_2 = (temp_5 >> 1) & 0xFFFFF800;
    M2C_FIELD(arg0, s32 *, 0x2DC) = temp_2;
    M2C_FIELD(arg0, s32 *, 0x2E4) = (s32) (temp_6 + temp_2);
}
