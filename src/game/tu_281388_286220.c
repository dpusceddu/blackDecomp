#include "auto/prelude.h"

void func_00286220(s32 arg0, void *arg1, void *arg2, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4, f32 fparg5) {
    f32 temp_f12;
    f32 temp_f13;
    f32 temp_f14;
    f32 temp_f15;
    f32 temp_f16;
    f32 temp_f17;

    temp_f12 = fparg0 / fparg3;
    temp_f13 = fparg1 / fparg3;
    temp_f14 = fparg2 / fparg3;
    temp_f17 = fparg5 / fparg3;
    temp_f16 = fparg4 / fparg3;
    temp_f15 = fparg3 / fparg3;
    M2C_FIELD(arg1, f32 *, 0) = temp_f12;
    M2C_FIELD(arg1, f32 *, 4) = temp_f13;
    M2C_FIELD(arg1, f32 *, 8) = temp_f14;
    M2C_FIELD(arg1, f32 *, 0x14) = temp_f17;
    M2C_FIELD(arg1, f32 *, 0x10) = temp_f16;
    M2C_FIELD(arg1, f32 *, 0xC) = temp_f15;
    M2C_FIELD(arg2, f32 *, 0x14) = temp_f17;
    M2C_FIELD(arg2, f32 *, 0) = temp_f12;
    M2C_FIELD(arg2, f32 *, 4) = temp_f13;
    M2C_FIELD(arg2, f32 *, 8) = temp_f14;
    M2C_FIELD(arg2, f32 *, 0xC) = temp_f15;
    M2C_FIELD(arg2, f32 *, 0x10) = temp_f16;
}
