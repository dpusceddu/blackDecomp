#include "ps2/prelude.h"

void func_00135ED0(void *arg0, f32 fparg0, f32 fparg1) {
    if ((M2C_FIELD(arg0, u8 *, 0x3B7) == 0) && (M2C_FIELD(arg0, u8 *, 0x3B5) == 0)) {
        M2C_FIELD(arg0, f32 *, 0x310) = fparg0;
        M2C_FIELD(arg0, s8 *, 0x3B4) = 1;
        M2C_FIELD(arg0, f32 *, 0x314) = fparg1;
    }
}
