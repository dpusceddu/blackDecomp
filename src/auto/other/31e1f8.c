#include "auto/prelude.h"

extern s32 func_00317E40();
extern s32 func_003186F0();

s32 func_0031E1F8(s32 arg0, s32 arg1, s32 arg2) {
    if (M2C_FIELD(arg0, s32 *, 0x48) != 0) {
        return 0;
    }
    if ((u16) M2C_FIELD(arg0, u16 *, 0x46) >= 2U) {
        if (arg2 != 0) {
            M2C_FIELD(arg0, s32 *, 0x48) = func_00317E40(arg1, (s32) M2C_FIELD(arg0, u16 *, 0x46), 1 << ((u32) M2C_FIELD(arg0, u32 *, 0x40) >> 0x1C), 1, 0, 0x3080A);
            M2C_FIELD(arg0, s32 *, 0xC) = (s32) (M2C_FIELD(arg0, s32 *, 0xC) | 0x40);
        } else {
            M2C_FIELD(arg0, s32 *, 0x48) = func_003186F0(arg1, (s32) M2C_FIELD(arg0, u16 *, 0x46), 1 << ((u32) M2C_FIELD(arg0, u32 *, 0x40) >> 0x1C), 1, 0);
            M2C_FIELD(arg0, s32 *, 0xC) = (s32) (M2C_FIELD(arg0, s32 *, 0xC) | 0x80);
        }
    } else {
        M2C_FIELD(arg0, s32 *, 0x48) = 1;
    }
    return (M2C_FIELD(arg0, s32 *, 0x48) != 0) ? arg0 : 0;
}
