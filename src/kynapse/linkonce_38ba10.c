#include "ps2/prelude.h"

extern u8 D_003E7550;

M2C_UNK * func_0038BA10(M2C_UNK *arg0) {
    if (D_003E7550 != 0) {
        M2C_FIELD(arg0, s32 *, 0x400) = 0;
    }
    D_003E7550 = 0;
    return arg0;
}
