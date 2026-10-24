#include "ps2/prelude.h"

extern s32 func_00176EE0(s32);

void func_00172518(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x1B5) = 1;
}

void func_00172528(s32 arg0) {
    func_00176EE0(arg0 + 0x14);
}
