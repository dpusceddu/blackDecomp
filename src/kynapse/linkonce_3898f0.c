#include "ps2/prelude.h"

void func_003898F0(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 8) = fparg0;
    M2C_FIELD(arg0, s8 *, 4) = 1;
}

f32 func_00389900(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 8);
}
