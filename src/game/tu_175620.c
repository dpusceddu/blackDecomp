#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001749C8();

s32 func_00175620(void) {
    return 1;
}

void func_00175628(void *arg0, void *arg1) {
    if (M2C_FIELD(arg1, s32 *, 0x1EF4) == M2C_FIELD(arg0, s8 *, 0x29)) {
        M2C_FIELD(arg0, s8 *, 0x29) = -1;
    }
}

void func_00175648(void) {
    func_001749C8();
}
