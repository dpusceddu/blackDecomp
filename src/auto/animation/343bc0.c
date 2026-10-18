#include "auto/prelude.h"

void * func_00343BC0(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2) {
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) (M2C_FIELD(arg0, f32 *, 0x10) * fparg0);
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) (M2C_FIELD(arg0, f32 *, 0x14) * fparg1);
    M2C_FIELD(arg0, f32 *, 0x18) = (f32) (M2C_FIELD(arg0, f32 *, 0x18) * fparg2);
    return arg0;
}

void * func_00343BF0(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) -M2C_FIELD(arg0, f32 *, 0x10);
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) -M2C_FIELD(arg0, f32 *, 0x14);
    M2C_FIELD(arg0, f32 *, 0x18) = (f32) -M2C_FIELD(arg0, f32 *, 0x18);
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) -M2C_FIELD(arg0, f32 *, 0xC);
    return arg0;
}
