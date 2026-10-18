#include "auto/prelude.h"

void * func_0038A240(void *arg0, void *arg1) {
    void *temp_5;

    temp_5 = arg1 + 4;
    M2C_FIELD(arg0, f32 *, 0) = (f32) M2C_FIELD(arg1, f32 *, 4);
    M2C_FIELD(arg0, f32 *, 4) = (f32) M2C_FIELD(temp_5, f32 *, 4);
    M2C_FIELD(arg0, f32 *, 8) = (f32) M2C_FIELD(temp_5, f32 *, 8);
    return arg0;
}
