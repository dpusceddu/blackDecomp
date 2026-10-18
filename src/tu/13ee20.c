#include "auto/prelude.h"

void func_0013EE20(void) {

}

s32 func_0013EE28(void) {
    return 1;
}

void func_0013EE30(void) {

}

void func_0013EE38(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x78) = 1;
}

void func_0013EE48(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x78) = 0;
}

void func_0013EE50(void) {

}

void func_0013EE58(void) {

}

void func_0013EE60(void) {

}

f32 func_0013EE68(void *arg0) {
    f32 var_f3;

    var_f3 = M2C_FIELD(arg0, f32 *, 0) - M2C_FIELD(arg0, f32 *, 4);
    if (var_f3 < -180.0f) {
        var_f3 += 360.0f;
    } else if (var_f3 > 180.0f) {
        var_f3 -= 360.0f;
    }
    if (M2C_FIELD(arg0, f32 *, 0x74) > 0.01f) {
        var_f3 -= 5.0f;
    }
    return var_f3;
}

f32 func_0013EF08(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0xC);
}

void func_0013EF10(void *arg0, s128 arg1, s32 arg2) {
    M2C_FIELD(arg0, s128 *, 0x50) = arg1;
    if (arg2 != 0) {
        M2C_FIELD(arg0, s128 *, 0x60) = arg1;
    }
}
