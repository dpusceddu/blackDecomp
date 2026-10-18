/* Translation unit kynapse/tu_2d1610 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_002E00F0();
extern M2C_UNK D_0044ECD0;
extern M2C_UNK func_002D1610;
extern M2C_UNK * D_0044EDE0;
extern M2C_UNK D_003E2AE0;
extern M2C_UNK D_003E2A58;
extern s32 (*D_003C87E0)();
extern s32 func_002DFF98();

void func_002D2CE8(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E00F0(&D_0044ECD0, "CFleeAgent", &func_002D1610, 0, 0, 0);
            return;
        }
        D_0044EDE0 = &D_003E2AE0;
    }
}

/* Assembly between the functions: func_002D2D48 (112 bytes) */

s32 func_002D2DB8(s32 arg0, s32 arg1) {
    s32 temp_4;
    s32 temp_4_2;
    s32 var_2;

    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E2A58;
    temp_4 = M2C_FIELD(arg0, s32 *, 0x1C);
    if (temp_4 != 0) {
        D_003C87E0(temp_4 - 0x10);
    }
    temp_4_2 = M2C_FIELD(arg0, s32 *, 0x28);
    if (temp_4_2 != 0) {
        D_003C87E0(temp_4_2);
    }
    func_002DFF98(arg0, 0);
    var_2 = arg1 & 1;
    if (var_2 != 0) {
        var_2 = D_003C87E0(arg0);
    }
    return var_2;
}

/* Assembly between the functions: func_002D2E48 (32 bytes), func_002D2E68 (40 bytes), func_002D2E90 (88 bytes) */

void func_002D2EE8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x40) = 0x7FFFFFFF;
}

/* Assembly between the functions: func_002D2F00 (64 bytes) */

void func_002D2F40(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
}

/* Assembly between the functions: func_002D2F48 (56 bytes) */

f32 func_002D2F80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0) {
    return (fparg0 / (f32) (arg3 + 1)) / (f32) ((arg2 * 0xA) + 1);
}

void func_002D2FB8(void) {
    func_002D2CE8(1, 0xFFFF);
}

void func_002D2FD8(void) {
    func_002D2CE8(0, 0xFFFF);
}
