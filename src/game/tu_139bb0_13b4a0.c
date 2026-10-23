#include "auto/prelude.h"

void func_0013B4A0(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2) {
    f32 temp_f0;

    temp_f0 = M2C_FIELD(arg0, f32 *, 0x4C4);
    M2C_FIELD(arg0, f32 *, 0x4C8) = fparg2;
    M2C_FIELD(arg0, f32 *, 0x4C4) = (f32) (temp_f0 + ((fparg0 - temp_f0) * fparg1));
}
