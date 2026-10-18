#include "auto/prelude.h"

s32 func_00322ED8(void) {
    return 0;
}

s32 func_00322EE0(s32 arg0, s32 arg1, void *arg2) {
    M2C_FIELD(M2C_FIELD(arg2, void **, 4), s32 *, 0) = arg0;
    M2C_FIELD(M2C_FIELD(arg2, void **, 4), s32 (**)(), 4) = func_00322ED8;
    M2C_FIELD(M2C_FIELD(arg2, void **, 4), s32 *, 8) = (s32) M2C_FIELD(arg2, s32 *, 0);
    return arg0;
}
