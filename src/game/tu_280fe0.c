#include "auto/prelude.h"

void func_00280FE0(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 8) = arg1;
    M2C_FIELD(arg0, s8 *, 4) = 1;
    if (arg1 != NULL) {
        M2C_FIELD(arg0, s32 *, 0xC) = (s32) M2C_FIELD(arg1, s32 *, 8);
        return;
    }
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
}

s32 func_00281008(void) {
    return 0;
}
