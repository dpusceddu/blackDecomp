/* Translation unit kynapse/tu_2d65e8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_002E00F0();
extern M2C_UNK D_0044F248;
extern M2C_UNK func_002D65E8;
extern M2C_UNK * D_0044F358;
extern M2C_UNK D_003E2AE0;
extern M2C_UNK D_003E3888;
extern s32 func_002DFF98();
extern s32 (*D_003C87E0)();
extern void * D_003C9ED4;

void func_002D6FA8(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E00F0(&D_0044F248, "CShooterAgent", &func_002D65E8, 0, 0, 0);
            return;
        }
        D_0044F358 = &D_003E2AE0;
    }
}

/* Assembly between the functions: func_002D7008 (96 bytes) */

s32 func_002D7068(s32 arg0, s32 arg1) {
    s32 var_2;

    M2C_FIELD(arg0, u32 *, 0) = &D_003E3888;
    var_2 = func_002DFF98(arg0, 0);
    if (arg1 & 1) {
        var_2 = D_003C87E0(arg0);
    }
    return var_2;
}

/* Assembly between the functions: func_002D70C0 (32 bytes), func_002D70E0 (40 bytes), func_002D7108 (16 bytes), func_002D7118 (208 bytes) */

void func_002D71E8(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) (fparg0 * M2C_FIELD(D_003C9ED4, f32 *, 0xC));
}

f32 func_002D7200(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0x10) / M2C_FIELD(D_003C9ED4, f32 *, 0xC);
}

void func_002D7220(void) {
    func_002D6FA8(1, 0xFFFF);
}

void func_002D7240(void) {
    func_002D6FA8(0, 0xFFFF);
}
