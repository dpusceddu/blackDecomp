#include "auto/prelude.h"

extern void * D_0040F4D0;

void func_00177C08(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
}

void func_00177C10(void *arg0, f32 fparg0) {
    f32 var_f12;

    var_f12 = fparg0;
    if (var_f12 < 1.0f) {
        var_f12 = 1.0f;
    }
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) (M2C_FIELD(D_0040F4D0, f32 *, 0x20) + var_f12);
}

s32 func_00177C48(void *arg0) {
    s32 var_2;

    var_2 = 1;
    if (!(M2C_FIELD(arg0, f32 *, 0x10) < M2C_FIELD(D_0040F4D0, f32 *, 0x20))) {
        var_2 = 0;
    }
    return var_2;
}

void func_00177C78(void *arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x40) = arg0;
    M2C_FIELD(arg1, void **, 0x2C) = (void *) M2C_FIELD(arg0, void **, 0x2C);
    M2C_FIELD(arg0, void **, 0x2C) = arg1;
}
