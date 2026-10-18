#include "auto/prelude.h"

extern s32 func_0030FD68();

void func_00310190(s32 arg0, void *arg1) {
    if (arg0 == M2C_FIELD(arg1, s32 *, 0x18)) {
        M2C_FIELD(arg1, s32 *, 0x18) = 0;
        M2C_FIELD(arg1, s8 *, 0x50) = 1;
    }
    if (arg0 == M2C_FIELD(arg1, s32 *, 0x1C)) {
        M2C_FIELD(arg1, s32 *, 0x1C) = 0;
        M2C_FIELD(arg1, s8 *, 0x50) = 1;
    }
    if (arg0 == M2C_FIELD(arg1, s32 *, 0x20)) {
        M2C_FIELD(arg1, s32 *, 0x20) = 0;
        M2C_FIELD(arg1, s8 *, 0x50) = 1;
    }
    if (arg0 == M2C_FIELD(arg1, s32 *, 0x24)) {
        M2C_FIELD(arg1, s32 *, 0x24) = 0;
        M2C_FIELD(arg1, s8 *, 0x50) = 1;
    }
    if (arg0 == M2C_FIELD(arg1, s32 *, 0x28)) {
        M2C_FIELD(arg1, s32 *, 0x28) = 0;
        M2C_FIELD(arg1, s8 *, 0x50) = 1;
    }
    if (arg0 == M2C_FIELD(arg1, s32 *, 0x2C)) {
        M2C_FIELD(arg1, s32 *, 0x2C) = 0;
        M2C_FIELD(arg1, s8 *, 0x50) = 1;
    }
}

void func_00310228(void) {
    func_0030FD68(1, 0xFFFF);
}

void func_00310248(void) {
    func_0030FD68(0, 0xFFFF);
}
