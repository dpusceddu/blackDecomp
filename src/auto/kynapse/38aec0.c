#include "auto/prelude.h"

void func_0038AEC0(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 8) = fparg0;
    M2C_FIELD(arg0, s8 *, 4) = 1;
}

f32 func_0038AED0(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 8);
}
