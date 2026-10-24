#include "ps2/prelude.h"

extern s32 func_00165BC8();

void func_0014C548(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x110) = arg1;
}

s32 func_0014C550(s32 arg0) {
    return func_00165BC8(arg0, (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x110), u8 *, 4));
}
