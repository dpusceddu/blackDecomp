#include "include_asm.h"
#include "ps2/prelude.h"

void func_0038AA68(void *arg0, f32 fparg0) {
    if (fparg0 >= 0.0f) {
        M2C_FIELD(arg0, f32 *, 4) = fparg0;
        return;
    }
    M2C_FIELD(arg0, f32 *, 4) = 0.0f;
}
