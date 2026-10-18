#include "auto/prelude.h"

void func_003281B0(void *arg0, f32 fparg0) {
    if (M2C_FIELD(arg0, s32 *, 0x58) & 2) {
        M2C_FIELD(arg0, f32 *, 0x9C) = fparg0;
        M2C_FIELD(arg0, u16 *, 0x5C) = (u16) (M2C_FIELD(arg0, u16 *, 0x5C) | 0x100);
    }
}
