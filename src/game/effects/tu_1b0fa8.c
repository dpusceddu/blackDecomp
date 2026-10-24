#include "include_asm.h"
#include "ps2/prelude.h"

void func_001B0FA8(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x174) = fparg0;
    M2C_FIELD(arg0, s32 *, 0x168) = arg1;
    M2C_FIELD(arg0, s32 *, 0x16C) = arg2;
    M2C_FIELD(arg0, s32 *, 0x170) = arg3;
}
