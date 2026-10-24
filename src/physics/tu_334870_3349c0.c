/* Translation unit physics/tu_334870 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_00334870();
extern s32 func_00334870(M2C_UNK, M2C_UNK);

void * func_003349C0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = 0x10;
    M2C_FIELD(arg0, s32 *, 0) = (s32) ((arg1 * 0x60) + 0x40);
    return arg0;
}

/* Assembly between the functions: func_003349E0 (104 bytes), func_00334A48 (8 bytes), func_00334A50 (200 bytes), func_00334B18 (48 bytes), func_00334B48 (16 bytes) */

void func_00334B58(void) {
    func_00334870(1, 0xFFFF);
}

void func_00334B78(void) {
    func_00334870(0, 0xFFFF);
}
