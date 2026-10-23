#include "auto/prelude.h"

void func_0026BC50(void *arg0, f32 fparg0) {
    if (fparg0 < 0.0f) {
        M2C_FIELD(arg0, f32 *, 0xCC) = (f32) -fparg0;
        return;
    }
    M2C_FIELD(arg0, f32 *, 0xCC) = fparg0;
}

s32 func_0026BC80(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xEC);
}
