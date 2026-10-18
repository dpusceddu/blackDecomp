#include "auto/prelude.h"

void func_0032E2A0(void *arg0, void *arg1, s32 arg2) {
    s32 *temp_3;
    s32 *temp_3_2;
    u32 temp_2;
    u32 temp_2_2;

    if (arg2 != 0) {
        temp_2 = M2C_FIELD(arg1, u32 *, 0x60);
        temp_3 = ((temp_2 >> 5) * 4) + M2C_FIELD(arg0, s32 *, 0xA8);
        *temp_3 |= 1 << (temp_2 & 0x1F);
        return;
    }
    temp_2_2 = M2C_FIELD(arg1, u32 *, 0x60);
    temp_3_2 = ((temp_2_2 >> 5) * 4) + M2C_FIELD(arg0, s32 *, 0xA8);
    *temp_3_2 &= ~(1 << (temp_2_2 & 0x1F));
}
