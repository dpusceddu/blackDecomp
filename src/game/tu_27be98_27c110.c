/* Translation unit tu_27be98 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_0027C2A8(s8 *arg0, s32 arg1);
extern s32 func_0035CCD8();

s32 func_0027C110(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x2011C) = arg1;
    return 1;
}

/* Assembly between the functions: func_0027C128 (112 bytes), func_0027C198 (8 bytes) */

void func_0027C1A0(void) {

}

/* Assembly between the functions: func_0027C1A8 (8 bytes), func_0027C1B0 (192 bytes), func_0027C270 (8 bytes) */

void func_0027C278(s8 *arg0) {
    func_0027C2A8(arg0, func_0035CCD8());
}
