#include "auto/prelude.h"

extern void func_0016E780();

void func_0016E728(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_16;

    temp_16 = (arg2 != 0) ? 2 : 1;
    if (M2C_FIELD(arg0, s32 *, 0x22BC8) < temp_16) {
        func_0016E780();
        M2C_FIELD(arg0, s32 *, 0x22BC8) = temp_16;
    }
}
