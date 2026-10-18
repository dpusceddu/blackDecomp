#include "auto/prelude.h"

extern s32 func_00125E40();

s32 func_0014F348(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x158) = 0;
    M2C_FIELD(arg0, u8 *, 0x152) = (u8) (M2C_FIELD(arg0, u8 *, 0x152) & 0xFB);
    return func_00125E40(arg0);
}
