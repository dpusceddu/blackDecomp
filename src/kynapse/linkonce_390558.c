#include "auto/prelude.h"

void func_00390558(void *arg0, void *arg1, f32 fparg0) {
    void *temp_2;

    temp_2 = arg0 + 4;
    M2C_FIELD(arg0, f32 *, 4) = (f32) M2C_FIELD(arg1, f32 *, 0);
    M2C_FIELD(temp_2, f32 *, 4) = (f32) M2C_FIELD(arg1, f32 *, 4);
    M2C_FIELD(temp_2, f32 *, 8) = (f32) M2C_FIELD(arg1, f32 *, 8);
    M2C_FIELD(arg0, f32 *, 0x10) = fparg0;
}

void func_00390580(void *arg0, void *arg1, f32 *arg2) {
    void *temp_2;

    temp_2 = arg0 + 4;
    M2C_FIELD(arg1, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 4);
    M2C_FIELD(arg1, f32 *, 4) = (f32) M2C_FIELD(temp_2, f32 *, 4);
    M2C_FIELD(arg1, f32 *, 8) = (f32) M2C_FIELD(temp_2, f32 *, 8);
    *arg2 = M2C_FIELD(arg0, f32 *, 0x10);
}
