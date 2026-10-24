#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_00173190();

void func_0016E728(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_16;

    temp_16 = (arg2 != 0) ? 2 : 1;
    if (M2C_FIELD(arg0, s32 *, 0x22BC8) < temp_16) {
        func_0016E780();
        M2C_FIELD(arg0, s32 *, 0x22BC8) = temp_16;
    }
}

void func_0016E780(void *arg0) {
    func_00173190(arg0 + 0x22800);
}
