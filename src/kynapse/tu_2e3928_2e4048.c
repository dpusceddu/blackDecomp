/* Translation unit kynapse/tu_2e3928 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_002E4070();
extern s32 func_00107D48();
extern s32 func_002E3F28(M2C_UNK, M2C_UNK);

s32 func_002E4048(s32 arg0) {
    func_002E4070();
    return arg0;
}

/* Assembly between the functions: func_002E4070 (240 bytes) */

void func_002E4160(s32 arg0, s32 arg1) {
    if (arg1 & 1) {
        func_00107D48(arg0);
    }
}

/* Assembly between the functions: func_002E4188 (16 bytes) */

void func_002E4198(void) {
    func_002E3F28(1, 0xFFFF);
}

void func_002E41B8(void) {
    func_002E3F28(0, 0xFFFF);
}
