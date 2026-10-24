#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_0012EEB8(s32 arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 4) + arg0;
    M2C_FIELD(arg0, s32 *, 4) = temp_2;
    return temp_2;
}
