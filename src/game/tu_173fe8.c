#include "auto/prelude.h"

s32 func_00173FE8(s16 *arg0) {
    *arg0 = 0;
    return 1;
}

void func_00173FF8(u16 *arg0, void *arg1) {
    *arg0 |= (s32) (0x10000 << M2C_FIELD(arg1, s32 *, 0x1EF4)) >> 0x10;
}

void func_00174018(u16 *arg0, void *arg1) {
    *arg0 &= ~((s32) (0x10000 << M2C_FIELD(arg1, s32 *, 0x1EF4)) >> 0x10);
}
