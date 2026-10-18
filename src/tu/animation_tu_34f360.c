/* Translation unit animation/tu_34f360 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_00343FC8();
extern s32 func_00344008();
extern s32 func_003474F8(s32, s32, f32);
extern s32 func_00343FE0();
extern s32 func_003438E0();
extern s32 func_00343BC0(s32, f32, f32, f32);

void * func_0034F360(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_UNK *temp_17;
    M2C_UNK *temp_18;
    M2C_UNK *temp_19;
    M2C_UNK *temp_20;
    M2C_UNK *temp_21;

    temp_17 = arg0 + 0x30;
    temp_18 = arg0 + 0x50;
    temp_19 = arg0 + 0x70;
    temp_20 = arg0 + 0x90;
    temp_21 = arg0 + 0x10;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 8) = arg3;
    M2C_FIELD(arg0, s32 *, 4) = (s32) (arg3 - 1);
    func_00343FC8(temp_21);
    func_00343FC8(temp_17);
    func_00343FC8(temp_18);
    func_00343FC8(temp_19);
    func_00343FC8(temp_20);
    func_00344008(temp_21);
    func_00344008(temp_17);
    func_00344008(temp_18);
    func_00344008(temp_19);
    func_00344008(temp_20);
    return arg0;
}

void * func_0034F420(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    return arg0;
}

/* Assembly between the functions: func_0034F430 (568 bytes), func_0034F668 (200 bytes), func_0034F730 (544 bytes) */

void func_0034F950(void *arg0, s32 arg1) {
    func_003474F8(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), (f32) arg1);
}

/* Assembly between the functions: func_0034F980 (80 bytes), func_0034F9D0 (144 bytes), func_0034FA60 (152 bytes) */

s32 func_0034FAF8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 sp[24] __attribute__((aligned(16)));
    func_00343FE0((s32) sp, arg3);
    return func_003438E0(arg1, (s32) sp, arg2, M2C_FIELD(M2C_FIELD(arg0, void **, 4), s32 *, 0xC));
}

/* Assembly between the functions: func_0034FB58 (296 bytes), func_0034FC80 (400 bytes) */

s32 func_0034FE10(void **arg0, s32 arg1) {
    f32 temp_f12;
    void *temp_4;

    temp_4 = *arg0;
    if (temp_4 != NULL) {
        temp_f12 = M2C_FIELD(temp_4, f32 *, 0x60);
        if (temp_f12 != 1.0f) {
            func_00343BC0(arg1, temp_f12, temp_f12, temp_f12);
        }
    }
    return arg1;
}
