#include "auto/prelude.h"

extern s32 func_00123BC8();
extern M2C_UNK D_0048EFA8;

void func_001240B0(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0x6A5) = arg1;
}

void func_001240B8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x58) = func_00123BC8(&D_0048EFA8);
}
