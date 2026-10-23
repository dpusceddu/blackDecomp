/* Translation unit physics/tu_335db8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_00335DB8(M2C_UNK, M2C_UNK);

void func_00335F00(void *arg0) {
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 0x3C);
    M2C_FIELD(arg0, s128 *, 0) = (s128) M2C_FIELD(temp_5, s128 *, 0x10);
    M2C_FIELD(arg0, s128 *, 0x10) = (s128) M2C_FIELD(temp_5, s128 *, 0x20);
}

/* Assembly between the functions: func_00335F18 (8 bytes), func_00335F20 (144 bytes) */

void func_00335FB0(void) {
    func_00335DB8(1, 0xFFFF);
}

void func_00335FD0(void) {
    func_00335DB8(0, 0xFFFF);
}
