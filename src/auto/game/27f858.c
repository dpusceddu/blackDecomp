#include "auto/prelude.h"

extern s32 func_0027F890();

void func_0027F858(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x28) != 0) {
        func_0027F890();
        M2C_FIELD(arg0, u8 *, 0x28) = 0U;
    }
}
