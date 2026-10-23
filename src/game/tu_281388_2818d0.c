/* Translation unit tu_281388 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_00284298(void *arg0);
extern s32 func_00285190(void *arg0);
extern s32 func_002819E0();
extern s32 func_00280908(s32, s32);
extern s32 func_002811E8();
extern s32 func_002726D0();
extern s32 func_00280E10();
extern s64 func_00272580();

void func_002818D0(s32 arg0, void *arg1) {
    func_00284298(arg1);
    M2C_FIELD(arg1, u16 *, 0x30) = (u16) (M2C_FIELD(arg1, u16 *, 0x30) & 0xFFFE);
}

void func_00281908(s32 arg0, void *arg1) {
    func_00285190(arg1);
    M2C_FIELD(arg1, u16 *, 0x30) = (u16) (M2C_FIELD(arg1, u16 *, 0x30) & 0xFFFE);
}

/* Assembly between the functions: func_00281940 (8 bytes) */

void func_00281948(s32 arg0, s32 arg1) {
    func_002819E0();
    func_00281988(arg0, arg1);
}

void func_00281988(s32 arg0, s32 arg1) {
    s32 var_16;
    u32 var_17;

    var_16 = arg0 + 0xE00;
    var_17 = 0;
    do {
        func_00280908(var_16, arg1);
        var_17 += 1;
        var_16 += 0x3C;
    } while (var_17 < 0x23U);
}

/* Assembly between the functions: func_002819E0 (88 bytes) */

void func_00281A38(s32 arg0, s32 arg1) {
    func_002811E8(arg1);
}

/* Assembly between the functions: func_00281A58 (128 bytes), func_00281AD8 (120 bytes) */

void * func_00281B50(void *arg0) {
    s32 temp_2;
    s32 temp_2_2;
    void *var_3;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x182C);
    var_3 = NULL;
    if (temp_2 != 0) {
        temp_2_2 = temp_2 - 1;
        M2C_FIELD(arg0, s32 *, 0x182C) = temp_2_2;
        var_3 = (M2C_FIELD((arg0 + temp_2_2), u8 *, 0x17C4) * 0x38) + arg0;
    }
    return var_3;
}

/* Assembly between the functions: func_00281B88 (48 bytes) */

s32 func_00281BB8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;
    s32 var_3;
    s32 var_5;
    s32 var_7;

    var_5 = arg1;
    M2C_FIELD(arg0, s32 *, 0xC0) = arg2;
    var_7 = 0;
    if (arg2 > 0) {
        var_3 = arg0;
        do {
            temp_2 = M2C_FIELD(var_5, s32 *, 0);
            var_7 += 1;
            M2C_FIELD(var_3, s32 *, 4) = 0;
            var_5 += 4;
            M2C_FIELD(var_3, s32 *, 0) = temp_2;
            var_3 += 0xC;
        } while (var_7 < M2C_FIELD(arg0, s32 *, 0xC0));
    }
    return 1;
}

/* Assembly between the functions: func_00281BF8 (160 bytes), func_00281C98 (184 bytes), func_00281D50 (208 bytes), func_00281E20 (8 bytes), func_00281E28 (184 bytes) */

void func_00281EE0(void *arg0, s64 *arg1, s32 arg2) {
    u8 sp[24] __attribute__((aligned(16)));
    s64 temp_5;

    temp_5 = *arg1;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s64 *, 0) = temp_5;
    if (arg2 != 0) {
        func_002726D0(temp_5, sp);
        if ((func_00280E10((s8) *(s32 *)(sp + 11), (sp + 16)) != 0) && (func_00280E10((s8) *(s32 *)(sp + 10), (sp + 17)) != 0)) {
            M2C_FIELD(arg0, u8 *, 0xC) = *(u8 *)(sp + 16);
            M2C_FIELD(arg0, s8 *, 0xD) = (s8) (*(u8 *)(sp + 17) - 1);
        } else {
            M2C_FIELD(arg0, s8 *, 0xD) = 0;
            M2C_FIELD(arg0, u8 *, 0xC) = 1U;
        }
        M2C_FIELD(arg0, s64 *, 0) = func_00272580(M2C_FIELD(arg0, s64 *, 0), 0, 9);
    }
}
