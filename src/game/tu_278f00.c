#include "auto/prelude.h"

extern s32 func_00274138();

void func_00278F00(void *arg0, s32 arg1, s32 arg2) {
    func_00274138(M2C_FIELD(arg0, s32 *, 0x2C) + (arg1 * 0x10) + 4, arg2 - 8);
}
