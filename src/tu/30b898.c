#include "auto/prelude.h"

extern s32 func_003071A8();
extern f32 D_003CD89C;

void func_0030B898(void) {
    func_003071A8();
}

void func_0030B8B8(f32 fparg0) {
    if (fparg0 >= 0.0f) {
        D_003CD89C = fparg0;
    }
}

void func_0030B8E0(void *arg0, f32 fparg0) {
    if (fparg0 >= 0.0f) {
        M2C_FIELD(arg0, f32 *, 0xE8) = fparg0;
    }
}

void func_0030B900(void *arg0, f32 fparg0) {
    if (fparg0 >= 0.0f) {
        M2C_FIELD(arg0, f32 *, 0xEC) = fparg0;
    }
}

void func_0030B920(void *arg0, f32 fparg0) {
    if (fparg0 > 0.0f) {
        M2C_FIELD(arg0, f32 *, 0xF0) = (f32) (fparg0 * 0.5f);
    }
}

void func_0030B958(void *arg0, f32 fparg0) {
    if (fparg0 > 0.0f) {
        M2C_FIELD(arg0, f32 *, 0xF4) = (f32) (fparg0 * M2C_FIELD(arg0, f32 *, 8));
    }
}
