#include "auto/prelude.h"

extern s32 func_0013ED98();

s32 func_0013EC10(s32 arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x80) = arg1;
    M2C_FIELD(arg0, s32 *, 0x7C) = 0;
    M2C_FIELD(arg0, s8 *, 0x78) = 0;
    return func_0013ED98(arg0);
}
