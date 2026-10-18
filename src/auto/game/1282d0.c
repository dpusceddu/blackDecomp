#include "auto/prelude.h"

s32 func_001282D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 4) + arg0;
    M2C_FIELD(arg0, s32 *, 4) = temp_2;
    return temp_2;
}
