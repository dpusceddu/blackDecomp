#include "auto/prelude.h"

extern s32 func_0013EC10();

s32 func_001306A0(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_0013EC10(arg0, 0);
    M2C_FIELD(arg0, s8 *, 0x102) = 0;
    return temp_v0;
}
