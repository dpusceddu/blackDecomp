#include "auto/prelude.h"

extern M2C_UNK D_003E12F8;
extern s32 func_002486D8(s32, M2C_UNK);
extern s32 func_00107D48(s32);
extern s32 func_002487E0(s32);
extern s32 func_00250198(s32, void *, s32);
extern s32 D_0043DEE0;
extern s32 func_002486D8();
extern s32 func_00250198();

void func_003865C0(void) {

}

void func_003865C8(void *arg0, s32 arg1) {
    s32 temp_4;

    M2C_FIELD(arg0, M2C_UNK **, 0x14) = &D_003E12F8;
    temp_4 = M2C_FIELD(arg0, s32 *, 0xC);
    if (temp_4 != 0) {
        func_002486D8(temp_4, 3);
    }
    if (arg1 & 1) {
        func_00107D48((s32) arg0);
    }
}

void func_00386628(void *arg0) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0xC);
    if (temp_4 != 0) {
        func_002487E0(temp_4);
    }
    M2C_FIELD(arg0, s8 *, 0x10) = 1;
}

void func_00386668(void *arg0, s32 arg1) {
    func_00250198(D_0043DEE0, arg0, arg1);
}

void func_00386698(void *arg0, s32 arg1) {
    func_00250198(D_0043DEE0, arg0, arg1);
}

void func_003866C8(void *arg0, s32 arg1) {
    func_00250198(D_0043DEE0, arg0, arg1);
}

void func_003866F8(u16 *arg0, s32 arg1) {
    void *temp_4;

    M2C_FIELD(arg0, M2C_UNK **, 0x14) = &D_003E12F8;
    temp_4 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_4 != NULL) {
        func_002486D8(temp_4, 3);
    }
    if (arg1 & 1) {
        func_00250198(D_0043DEE0, arg0, 0x18);
    }
}

void func_00386760(u16 *arg0, s32 arg1) {
    void *temp_4;

    M2C_FIELD(arg0, M2C_UNK **, 0x14) = &D_003E12F8;
    temp_4 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_4 != NULL) {
        func_002486D8(temp_4, 3);
    }
    if (arg1 & 1) {
        func_00250198(D_0043DEE0, arg0, 0x18);
    }
}

void func_003867C8(u16 *arg0, s32 arg1) {
    void *temp_4;

    M2C_FIELD(arg0, M2C_UNK **, 0x14) = &D_003E12F8;
    temp_4 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_4 != NULL) {
        func_002486D8(temp_4, 3);
    }
    if (arg1 & 1) {
        func_00250198(D_0043DEE0, arg0, 0x1C);
    }
}
