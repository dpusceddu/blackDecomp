#include "auto/prelude.h"

extern void func_00181AD0(void *arg0, s32 arg1);

void func_0018D818(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x50) & 0xEF) {
        M2C_FIELD(arg0, u8 *, 0x50) = 0x10U;
        func_00181AD0(M2C_FIELD(arg0, s32 *, 0x1C) + 0xEC0, 0xD);
    }
}

void func_0018D858(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x50) = (u8) ((M2C_FIELD(arg0, u8 *, 0x50) & 0xFE) | 2);
}
