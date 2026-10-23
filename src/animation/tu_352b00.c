#include "auto/prelude.h"

extern M2C_UNK D_0046C608;

void func_00352B00(s32 arg0, s32 arg1) {
    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        M2C_FIELD(&D_0046C608, s32 *, 0) = 0;
        M2C_FIELD(&D_0046C608, s32 *, 8) = 0;
        M2C_FIELD(&D_0046C608, s32 *, 4) = 0;
    }
}
