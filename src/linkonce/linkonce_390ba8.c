#include "include_asm.h"
#include "ps2/prelude.h"

extern u8 D_003EDA28;

M2C_UNK * func_00390BA8(M2C_UNK *arg0) {
    if (D_003EDA28 != 0) {
        M2C_FIELD(arg0, s32 *, 0x400) = 0;
    }
    D_003EDA28 = 0;
    return arg0;
}
