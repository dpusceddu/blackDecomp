#include "auto/prelude.h"

void func_00389CF8(void *arg0, void *arg1) {
    void *temp_2;

    temp_2 = arg0 + 8;
    M2C_FIELD(arg0, f32 *, 8) = (f32) M2C_FIELD(arg1, f32 *, 0);
    M2C_FIELD(temp_2, f32 *, 4) = (f32) M2C_FIELD(arg1, f32 *, 4);
    M2C_FIELD(temp_2, f32 *, 8) = (f32) M2C_FIELD(arg1, f32 *, 8);
    M2C_FIELD(arg0, s8 *, 4) = 1;
}
