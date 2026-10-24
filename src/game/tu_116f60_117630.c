#include "ps2/prelude.h"

extern void func_00118900(s32);
extern s32 func_001175E0();
extern void func_00118340(s32);
extern s32 func_00118858();
extern s32 func_00116F68();
extern s32 func_00118290();
extern s32 func_001188E0();
extern s32 func_001175C0();
extern s32 func_00118320();
extern s32 func_00118098();
extern s32 func_00118898(void *, s32, f32);
extern s32 func_00116FA8(void *, s32, f32);
extern s32 func_001182D0(void *, s32, f32);
extern s32 func_00118810();

void func_00117630(s32 arg0) {
    func_00118900(arg0 + 4);
    func_001175E0(arg0 + 0x20);
    func_00118340(arg0 + 0x60);
}

s32 func_00117668(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, u8 *, 0xA0) != 0) {
        func_00118858(arg0 + 4);
    }
    if (M2C_FIELD(arg0, u8 *, 0xA1) != 0) {
        func_00116F68(arg0 + 0x20, arg1);
    }
    if (M2C_FIELD(arg0, u8 *, 0xA2) != 0) {
        func_00118290(arg0 + 0x60, arg1);
    }
    return 1;
}

void func_001176D0(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, u8 *, 0xA0) != 0) {
        func_001188E0(arg0 + 4);
    }
    if (M2C_FIELD(arg0, u8 *, 0xA1) != 0) {
        func_001175C0(arg0 + 0x20, arg1);
    }
    if (M2C_FIELD(arg0, u8 *, 0xA2) != 0) {
        func_00118320(arg0 + 0x60, arg1);
    }
}

void func_00117738(void *arg0, s32 arg1, f32 fparg0) {
    void *temp_16;
    void *temp_16_2;
    void *temp_16_3;

    if (M2C_FIELD(arg0, u8 *, 0xA0) != 0) {
        temp_16 = arg0 + 4;
        if (func_00118098(temp_16) == 0) {
            func_00118898(temp_16, arg1, fparg0);
        }
    }
    temp_16_2 = arg0 + 0x20;
    if ((M2C_FIELD(arg0, u8 *, 0xA1) != 0) && (func_00118098(temp_16_2) == 0)) {
        func_00116FA8(temp_16_2, arg1, fparg0);
    }
    temp_16_3 = arg0 + 0x60;
    if ((M2C_FIELD(arg0, u8 *, 0xA2) != 0) && (func_00118098(temp_16_3) == 0)) {
        func_001182D0(temp_16_3, arg1, fparg0);
    }
}

s32 func_00117800(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s8 *, 0xA0) = 1;
    return func_00118810(arg0 + 4);
}
