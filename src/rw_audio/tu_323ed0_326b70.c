/* Translation unit rwa_ee/tu_323ed0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_00311CA0(M2C_UNK *);
extern M2C_UNK D_0045BFF8;
extern s32 func_00310978();
extern M2C_UNK D_0045C020;
extern s32 func_003261B8();

s32 func_00326B70(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x6A4);
    return arg0;
}

/* Assembly between the functions: func_00326B80 (320 bytes), func_00326CC0 (48 bytes), func_00326CF0 (144 bytes), func_00326D80 (232 bytes), func_00326E68 (112 bytes) */

void func_00326ED8(void) {
    func_00311CA0(&D_0045BFF8);
}

/* Assembly between the functions: func_00326EF8 (376 bytes), func_00327070 (472 bytes), func_00327248 (2760 bytes), func_00327D10 (528 bytes) */

s32 func_00327F20(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return func_00310978((s32) &D_0045C020, arg0, arg2, arg1, arg3, arg4);
}

/* Assembly between the functions: func_00327F58 (112 bytes), func_00327FC8 (64 bytes), func_00328008 (208 bytes), func_003280D8 (48 bytes) */

s32 func_00328108(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;
    s32 temp_2_2;
    void *temp_3;
    void *temp_4;

    if (arg1 == 0) {
        temp_4 = M2C_FIELD(arg0, void **, 0x30);
        temp_2_2 = M2C_FIELD(temp_4, s32 *, 0x1C) & 0xFFFFFFFE;
        M2C_FIELD(temp_4, s32 *, 0x1C) = temp_2_2;
        return temp_2_2;
    }
    temp_3 = M2C_FIELD(arg0, void **, 0x30);
    temp_2 = M2C_FIELD(temp_3, s32 *, 0x1C) | 1;
    M2C_FIELD(temp_3, s32 *, 0x1C) = temp_2;
    return temp_2;
}

void func_00328140(void *arg0, void *arg1) {
    if (M2C_FIELD(arg0, void **, 0x38) != NULL) {
        *M2C_FIELD(arg0, s32 **, 0x30) = 1;
    }
    if (arg1 != NULL) {
        M2C_FIELD(arg0, s32 *, 0xBC) = (s32) (((s32) M2C_FIELD(arg1, s32 *, 0x54) >> 1) & 1);
    }
    M2C_FIELD(arg0, void **, 0x38) = arg1;
    M2C_FIELD(arg0, u16 *, 0x5C) = (u16) (M2C_FIELD(arg0, u16 *, 0x5C) | 0x40);
}

void func_00328180(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, u16 *, 0x5C) = (u16) (M2C_FIELD(arg0, u16 *, 0x5C) | 4);
    M2C_FIELD(arg0, f32 *, 0xA4) = (f32) ((fparg0 * 0.5f) + 0.5f);
}

/* Assembly between the functions: func_003281A8 (8 bytes) */

void func_003281B0(void *arg0, f32 fparg0) {
    if (M2C_FIELD(arg0, s32 *, 0x58) & 2) {
        M2C_FIELD(arg0, f32 *, 0x9C) = fparg0;
        M2C_FIELD(arg0, u16 *, 0x5C) = (u16) (M2C_FIELD(arg0, u16 *, 0x5C) | 0x100);
    }
}

s32 func_003281D8(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x40) = 0;
    return func_003261B8(arg0);
}

s32 func_003281F8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0) = 0x17;
    M2C_FIELD(arg1, s32 *, 4) = 0x30;
    return arg0;
}
