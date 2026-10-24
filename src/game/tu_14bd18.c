#include "ps2/prelude.h"

extern s32 func_00125C60();

void func_0014BD18(void *arg0) {
    func_00125C60();
    M2C_FIELD(arg0, s8 *, 0xD0) = 0;
    M2C_FIELD(arg0, s32 *, 0x11C) = 0;
    M2C_FIELD(arg0, s32 *, 0x120) = 0;
    M2C_FIELD(arg0, s8 *, 0x13D) = 0;
    M2C_FIELD(arg0, s8 *, 0x139) = 0;
    M2C_FIELD(arg0, s8 *, 0x13F) = 0;
}
