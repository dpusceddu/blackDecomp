#include "ps2/prelude.h"

extern s32 func_00182158();

s32 func_00182138(s32 arg0) {
    M2C_FIELD(arg0, s8 *, 0x36) = 0;
    return func_00182158(arg0);
}
