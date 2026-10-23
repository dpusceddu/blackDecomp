/* Translation unit tu_179400 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_00177A98();
extern s32 func_00177AD0();

s32 func_00179640(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x70) != 0;
}

void * func_00179650(void *arg0, s32 arg1) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x70), s32 *, 0x2C) + (arg1 * 0x50);
}

/* Assembly between the functions: func_00179668 (24 bytes), func_00179680 (24 bytes), func_00179698 (24 bytes), func_001796B0 (24 bytes), func_001796C8 (24 bytes) */

void func_001796E0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x74) != 0) {
        func_00179960(M2C_FIELD(arg0, s32 *, 0x70));
    }
}

/* Assembly between the functions: func_00179708 (176 bytes), func_001797B8 (40 bytes), func_001797E0 (32 bytes), func_00179800 (352 bytes) */

void func_00179960(void *arg0, s32 arg1) {
    s32 var_17;
    s32 var_18;

    var_18 = 0;
    if (M2C_FIELD(arg0, s32 *, 0x28) > 0) {
        var_17 = 0;
        do {
            if (func_00177A98(M2C_FIELD(arg0, s32 *, 0x2C) + var_17) == arg1) {
                func_00177AD0(M2C_FIELD(arg0, s32 *, 0x2C) + var_17);
            }
            var_18 += 1;
            var_17 += 0x50;
        } while (var_18 < M2C_FIELD(arg0, s32 *, 0x28));
    }
}
