#include "auto/prelude.h"

void func_001F35B8(void *arg0, f32 fparg0) {
    void *temp_2;

    temp_2 = arg0 + 0x98;
    M2C_FIELD(temp_2, f32 *, 4) = (f32) (M2C_FIELD(temp_2, f32 *, 4) * fparg0);
    M2C_FIELD(arg0, f32 *, 0x98) = (f32) (M2C_FIELD(arg0, f32 *, 0x98) * fparg0);
}
