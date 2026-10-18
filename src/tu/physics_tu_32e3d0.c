/* Translation unit physics/tu_32e3d0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_0032E3D0();
extern s32 func_0032E490(M2C_UNK, M2C_UNK);

void * func_0032E5D8(void *arg0) {
    u8 sp[24] __attribute__((aligned(16)));
    func_0032E3D0(sp);
    M2C_FIELD(arg0, s32 *, 4) = 0x80;
    M2C_FIELD(arg0, s32 *, 0) = *(s32 *)(sp + 16);
    return arg0;
}

/* Assembly between the functions: func_0032E618 (184 bytes) */

void func_0032E6D0(void) {
    func_0032E490(1, 0xFFFF);
}

void func_0032E6F0(void) {
    func_0032E490(0, 0xFFFF);
}
