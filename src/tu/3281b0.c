#include "auto/prelude.h"

extern s32 func_003261B8();

void func_003281B0(void *arg0, f32 fparg0) {
    if (M2C_FIELD(arg0, s32 *, 0x58) & 2) {
        M2C_FIELD(arg0, f32 *, 0x9C) = fparg0;
        M2C_FIELD(arg0, u16 *, 0x5C) = (u16) (M2C_FIELD(arg0, u16 *, 0x5C) | 0x100);
    }
}

s32 func_003281D8(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x40) = 0;
    return func_003261B8(arg0);
}

s32 func_003281F8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0) = 0x17;
    M2C_FIELD(arg1, s32 *, 4) = 0x30;
    return arg0;
}
