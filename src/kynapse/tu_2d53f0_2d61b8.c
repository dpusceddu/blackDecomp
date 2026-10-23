/* Translation unit kynapse/tu_2d53f0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_002E00F0();
extern M2C_UNK D_0044F130;
extern M2C_UNK func_002D53F0;
extern M2C_UNK * D_0044F240;
extern M2C_UNK D_003E2AE0;
extern s32 func_002DFF10();
extern M2C_UNK D_003E3688;
extern s32 func_002DFF98();
extern s32 (*D_003C87E0)();
extern void func_002D6480();

void func_002D61B8(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E00F0(&D_0044F130, "CPathWayAgent", &func_002D53F0, 0, 0, 0);
            return;
        }
        D_0044F240 = &D_003E2AE0;
    }
}

void * func_002D6218(void *arg0) {
    func_002DFF10();
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E3688;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    M2C_FIELD(arg0, s32 *, 0x34) = 0;
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    return arg0;
}

s32 func_002D6278(s32 arg0, s32 arg1) {
    s32 var_2;

    M2C_FIELD(arg0, u32 *, 0) = &D_003E3688;
    var_2 = func_002DFF98(arg0, 0);
    if (arg1 & 1) {
        var_2 = D_003C87E0(arg0);
    }
    return var_2;
}

/* Assembly between the functions: func_002D62D0 (240 bytes), func_002D63C0 (16 bytes), func_002D63D0 (16 bytes), func_002D63E0 (96 bytes) */

void func_002D6440(void) {
    func_002D6480();
}

/* Assembly between the functions: func_002D6460 (32 bytes), func_002D6480 (88 bytes) */

s32 func_002D64D8(s32 arg0) {
    u32 temp_6;
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 0x38);
    if (temp_5 != NULL) {
        goto block_2;
    }
    goto block_7;
block_2:
    temp_6 = M2C_FIELD(arg0, u32 *, 0x3C);
    if (temp_6 < (u32) M2C_FIELD(temp_5, u32 *, 8)) {
        goto block_5;
    }
    goto block_7;
block_5:
    return M2C_FIELD(temp_5, s32 *, 4) + (temp_6 * 0x58) + 4;
block_7:
    return M2C_FIELD(M2C_FIELD(arg0, void **, 8), s32 *, 0x14) + 0x30;
}

/* Assembly between the functions: func_002D6520 (96 bytes) */

s32 func_002D6580(void *arg0, u32 arg1) {
    if (arg1 < (u32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u32 *, 8)) {
        M2C_FIELD(arg0, u32 *, 0x3C) = arg1;
        return 1;
    }
    return 0;
}

void func_002D65A8(void) {
    func_002D61B8(1, 0xFFFF);
}

void func_002D65C8(void) {
    func_002D61B8(0, 0xFFFF);
}
