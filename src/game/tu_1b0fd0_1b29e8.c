#include "auto/prelude.h"

extern s32 func_001B2A20();

s32 func_001B29E8(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_001B2A20(arg0, M2C_FIELD(arg1, s32 *, 0), (s32) M2C_FIELD(arg1, u8 *, 4));
    M2C_FIELD(arg1, u8 *, 4) = 0U;
    M2C_FIELD(arg1, s32 *, 0) = 0;
    return temp_v0;
}
