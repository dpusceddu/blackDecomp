#include "ps2/prelude.h"

extern u8 D_003E6430;

M2C_UNK * func_0038B078(M2C_UNK *arg0) {
    if (D_003E6430 != 0) {
        M2C_FIELD(arg0, s32 *, 0x400) = 0;
    }
    D_003E6430 = 0;
    return arg0;
}
