#include "auto/prelude.h"

void func_0038A410(void *arg0, f32 fparg0) {
    if (fparg0 >= 0.0f) {
        M2C_FIELD(arg0, f32 *, 4) = fparg0;
        return;
    }
    M2C_FIELD(arg0, f32 *, 4) = 0.0f;
}
