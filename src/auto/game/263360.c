#include "auto/prelude.h"

extern s32 func_0032CDE0(s32, s32);

s32 func_00263360(void *arg0, s32 arg1) {
    func_0032CDE0(arg1, M2C_FIELD(arg0, s32 *, 8));
    return 1;
}

void func_00263388(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0xE) = 0;
}
