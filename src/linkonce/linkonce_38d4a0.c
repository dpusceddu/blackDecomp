#include "ps2/prelude.h"

extern u8 D_003C8C00;

M2C_UNK * func_0038D4A0(M2C_UNK *arg0) {
    if (D_003C8C00 != 0) {
        M2C_FIELD(arg0, s32 *, 0x400) = 0;
    }
    D_003C8C00 = 0;
    return arg0;
}
