#include "auto/prelude.h"

extern s32 func_0017B358();
extern s32 func_00173690();

void func_00180AE0(void *arg0, s128 arg1) {
    M2C_FIELD(arg0, s8 *, 0x70) = 1;
    M2C_FIELD(arg0, s128 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 0x74) = 2;
    func_0017B358(arg0 + 0x110);
    func_00173690(arg0 + 0x148);
    M2C_FIELD(arg0, s8 *, 0x14D) = 1;
    M2C_FIELD(arg0, s8 *, 0x14F) = 0;
}
