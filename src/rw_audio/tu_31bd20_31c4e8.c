/* Translation unit rwa_ee/tu_31bd20 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 * func_0031DEB8();
extern M2C_UNK D_0040A260;
extern void * func_00312C48();
extern s32 func_00312C70(void *);

s32 func_0031C4E8(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 (*temp_2)(s32, s32, s32, s32);
    s32 temp_2_2;
    s32 var_17;

    var_17 = 0;
    if (arg0 == func_0031DEB8(NULL, &D_0040A260, 0)) {
        var_17 = M2C_FIELD(arg1, s32 *, 8);
    }
    temp_2 = M2C_FIELD(arg1, s32 (**)(s32, s32, s32, s32), 0);
    if (temp_2 != NULL) {
        temp_2_2 = temp_2(arg0, M2C_FIELD(arg1, s32 *, 4), arg2, arg3);
        var_17 = (temp_2_2 != 0) ? temp_2_2 : var_17;
    }
    return var_17;
}

/* Assembly between the functions: func_0031C578 (136 bytes), func_0031C600 (224 bytes) */

u32 func_0031C6E0(void *arg0) {
    s32 temp_5;
    u32 var_2;
    void *temp_6;

    temp_6 = M2C_FIELD(M2C_FIELD(arg0, void **, 0xA8), void **, 0x90);
    temp_5 = M2C_FIELD(temp_6, s32 *, 0);
    if ((temp_5 != 3) && (temp_5 != 1)) {
        var_2 = M2C_FIELD(temp_6, u32 *, 0x14);
    } else {
        var_2 = M2C_FIELD(arg0, u32 *, 0x64);
    }
    return var_2 / (u32) M2C_FIELD(arg0, u32 *, 0xB4);
}

/* Assembly between the functions: func_0031C728 (136 bytes), func_0031C7B0 (16 bytes) */

void func_0031C7C0(void *arg0) {
    M2C_FIELD(arg0, void **, 0x50) = func_00312C48(M2C_FIELD(arg0, s32 *, 0x4C) * 0x18, 0x30809);
}

void func_0031C800(void *arg0) {
    func_00312C70(M2C_FIELD(arg0, void **, 0x50));
}

/* Assembly between the functions: func_0031C820 (248 bytes), func_0031C918 (72 bytes) */

void func_0031C960(void) {

}

s32 func_0031C968(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x9C) & 1;
}

/* Assembly between the functions: func_0031C978 (88 bytes) */

s32 func_0031C9D0(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x9C) & 4) {
        return M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0xA4) * 0x18) + M2C_FIELD(arg0, s32 *, 0x50)), s32 *, 0x14) == 0;
    }
    return 0;
}

/* Assembly between the functions: func_0031CA08 (192 bytes), func_0031CAC8 (176 bytes), func_0031CB78 (8 bytes), func_0031CB80 (216 bytes), func_0031CC58 (136 bytes), func_0031CCE0 (8 bytes), func_0031CCE8 (40 bytes) */

void * func_0031CD10(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s32 *, 0xCC) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 0xD0) = (s32) M2C_FIELD(arg1, s32 *, 0);
    return arg0;
}

/* Assembly between the functions: func_0031CD28 (128 bytes), func_0031CDA8 (32 bytes), func_0031CDC8 (32 bytes), func_0031CDE8 (72 bytes) */

s32 func_0031CE30(s32 arg0, s32 arg1) {
    *M2C_FIELD(arg0, s32 **, 0x90) = (M2C_FIELD(arg1, s32 *, 0) != 0) ? 2 : 1;
    return arg0;
}
