#include "ps2/prelude.h"

extern s32 func_00328140(void *, s32);
extern s32 func_003281B0(s32);
extern s32 func_00328180(s32);
extern s32 func_00328108(s32, s32);

void func_00283B10(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 4) = arg1;
    func_00328140(M2C_FIELD(arg0, void **, 0x38), M2C_FIELD(arg1, s32 *, 0x18));
}

void func_00283B38(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x35) == 0) {
        func_003281B0(M2C_FIELD(arg0, s32 *, 0x38));
    }
}

void func_00283B60(void *arg0) {
    func_00328180(M2C_FIELD(arg0, s32 *, 0x38));
}

void func_00283B80(void *arg0, f32 fparg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), f32 *, 0xB4) = fparg0;
}

void func_00283B90(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x24) = fparg0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), f32 *, 0xB8) = fparg0;
}

void func_00283BA0(void *arg0, s32 arg1) {
    void *temp_6;

    temp_6 = M2C_FIELD(arg0, void **, 0x38);
    M2C_FIELD(temp_6, u16 *, 0x5C) = (u16) (M2C_FIELD(temp_6, u16 *, 0x5C) | 0x80);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), void **, 0x30), s32 *, 0x18) = arg1;
}

void func_00283BC0(void *arg0, s32 arg1) {
    u16 temp_2;
    u16 var_2;

    func_00328108(M2C_FIELD(arg0, s32 *, 0x38), arg1 != 0);
    temp_2 = M2C_FIELD(arg0, u16 *, 0x30);
    if (arg1 != 0) {
        var_2 = temp_2 | 0x80;
    } else {
        var_2 = temp_2 & 0xFF7F;
    }
    M2C_FIELD(arg0, u16 *, 0x30) = var_2;
}

void func_00283C10(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x10) = fparg0;
}

void func_00283C18(void *arg0) {
    func_00328180(M2C_FIELD(arg0, s32 *, 0x38));
}
