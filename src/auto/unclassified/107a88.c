#include "auto/prelude.h"

extern s32 func_00107B08();

s32 func_00107A88(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_00107B08(arg0, 0, 0);
    M2C_FIELD(arg0, s8 *, 0x3B8) = 0;
    return temp_v0;
}
