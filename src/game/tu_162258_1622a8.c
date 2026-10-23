/* Translation unit tu_162258 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_00160ED8();
extern void * func_00135550();
extern s32 func_0013D8B8();
extern s32 func_001791D8();
extern void * D_0040F4D4;
extern s32 func_001623B8();
extern s32 func_001790D0();
extern s32 func_0013D8A0();

s32 func_001622A8(void) {
    func_00160ED8();
    return 1;
}

/* Assembly between the functions: func_001622C8 (8 bytes) */

void func_001622D0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x1C) != 0) {
        func_00162310();
        return;
    }
    M2C_FIELD(arg0, u8 *, 0x1C) = 1U;
    func_00162420(arg0);
}

void func_00162310(void *arg0) {
    s32 temp_5;
    s64 *temp_4;

    M2C_FIELD(arg0, s8 *, 0x1C) = 0;
    temp_4 = M2C_FIELD(arg0, s64 **, 0x20);
    if ((temp_4 != NULL) && (M2C_FIELD(temp_4, s32 *, 0x37C) == M2C_FIELD(arg0, s32 *, 0x2C)) && (func_00135550(temp_4) != NULL) && (M2C_FIELD(func_00135550(M2C_FIELD(arg0, s64 **, 0x20)), s32 *, 0x80) == 1)) {
        func_0013D8B8(func_00135550(M2C_FIELD(arg0, s64 **, 0x20)), arg0);
    }
    temp_5 = M2C_FIELD(arg0, s32 *, 0x30);
    if (temp_5 != -1) {
        func_001791D8(D_0040F4D4 + 0xFA8, temp_5);
        M2C_FIELD(arg0, s32 *, 0x30) = -1;
    }
    M2C_FIELD(arg0, s64 **, 0x20) = NULL;
}

/* Assembly between the functions: func_001623B8 (104 bytes) */

void func_00162420(void *arg0) {
    s64 *temp_2;

    temp_2 = func_001623B8();
    M2C_FIELD(arg0, s64 **, 0x24) = temp_2;
    if ((temp_2 != NULL) && (func_00135550(temp_2) != NULL) && (M2C_FIELD(func_00135550(M2C_FIELD(arg0, s64 **, 0x24)), s32 *, 0x80) == 1)) {
        M2C_FIELD(arg0, s32 *, 0x30) = func_001790D0(D_0040F4D4 + 0xFA8, arg0);
        func_0013D8A0(func_00135550(M2C_FIELD(arg0, s64 **, 0x24)), arg0);
    }
}

void func_001624A0(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x24);
    M2C_FIELD(arg0, void **, 0x20) = temp_3;
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(temp_3, s32 *, 0x37C);
    M2C_FIELD(arg0, u16 *, 0x28) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0x50), u16 *, 0x2C);
}

/* Assembly between the functions: func_001624C0 (176 bytes) */

s32 func_00162570(s32 arg0) {
    return arg0 + 0x40;
}
