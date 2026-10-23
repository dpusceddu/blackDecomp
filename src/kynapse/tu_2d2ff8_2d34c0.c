/* Translation unit kynapse/tu_2d2ff8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_002E00F0();
extern M2C_UNK D_0044EDE8;
extern M2C_UNK func_002D2FF8;
extern M2C_UNK * D_0044EEF8;
extern M2C_UNK D_003E2AE0;
extern s32 func_002DFF10();
extern M2C_UNK D_003E3130;
extern s32 func_002DFF98();
extern s32 (*D_003C87E0)();
extern void * D_003C9ED4;

void func_002D34C0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E00F0(&D_0044EDE8, "CFollowerAgent", &func_002D2FF8, 0, 0, 0);
            return;
        }
        D_0044EEF8 = &D_003E2AE0;
    }
}

void * func_002D3520(void *arg0) {
    func_002DFF10();
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E3130;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    return arg0;
}

s32 func_002D3560(s32 arg0, s32 arg1) {
    s32 var_2;

    M2C_FIELD(arg0, u32 *, 0) = &D_003E3130;
    var_2 = func_002DFF98(arg0, 0);
    if (arg1 & 1) {
        var_2 = D_003C87E0(arg0);
    }
    return var_2;
}

/* Assembly between the functions: func_002D35B8 (16 bytes), func_002D35C8 (16 bytes), func_002D35D8 (56 bytes), func_002D3610 (152 bytes), func_002D36A8 (304 bytes) */

void func_002D37D8(void *arg0, f32 fparg0) {
    f32 temp_f12;

    temp_f12 = fparg0 * M2C_FIELD(D_003C9ED4, f32 *, 0xC);
    if (M2C_FIELD(arg0, f32 *, 0x40) != temp_f12) {
        M2C_FIELD(arg0, f32 *, 0x40) = temp_f12;
        M2C_FIELD(arg0, s8 *, 0x38) = 0;
    }
}

void func_002D3810(void *arg0, f32 fparg0) {
    if (M2C_FIELD(arg0, f32 *, 0x44) != fparg0) {
        M2C_FIELD(arg0, f32 *, 0x44) = fparg0;
        M2C_FIELD(arg0, s8 *, 0x38) = 0;
    }
}

f32 func_002D3838(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0x40) / M2C_FIELD(D_003C9ED4, f32 *, 0xC);
}

/* Assembly between the functions: func_002D3858 (48 bytes) */

void func_002D3888(void) {
    func_002D34C0(1, 0xFFFF);
}

void func_002D38A8(void) {
    func_002D34C0(0, 0xFFFF);
}
