#include "auto/prelude.h"

extern void func_00181AD0(void *arg0, s32 arg1);

void func_0018D658(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x15) == 0) {
        M2C_FIELD(arg0, u8 *, 0x15) = 1U;
        func_00181AD0(M2C_FIELD(arg0, s32 *, 0x1C) + 0xEC0, 9);
    }
}

void func_0018D698(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x18) = arg1;
    func_00181AD0(M2C_FIELD(arg0, s32 *, 0x1C) + 0xEC0, 0xB);
}
