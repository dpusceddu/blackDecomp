#include "ps2/prelude.h"

extern s32 func_00164DF0();

void func_00164D30(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x195) == 0) {
        func_00164DF0();
        M2C_FIELD(arg0, u8 *, 0x195) = 1U;
    }
}
