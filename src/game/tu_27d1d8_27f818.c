#include "ps2/prelude.h"

extern s32 func_0027F890();

void func_0027F818(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x28) == 0) {
        func_0027F890();
        M2C_FIELD(arg0, u8 *, 0x28) = 1U;
    }
}
