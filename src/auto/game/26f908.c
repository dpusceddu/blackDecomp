#include "auto/prelude.h"

void func_0026F908(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x50) = 0xE;
    M2C_FIELD(arg0, s32 *, 0xD8) = -1;
    M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    M2C_FIELD(arg0, s32 *, 0x58) = arg1;
    M2C_FIELD(arg0, s32 *, 0xD0) = 0;
    if (arg1 == 3) {
        M2C_FIELD(arg0, s32 *, 0xD4) = 0;
        return;
    }
    M2C_FIELD(arg0, s32 *, 0xD4) = 1;
}
