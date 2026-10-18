/* Translation unit tu_17c908 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_0017E770();

void func_0017C9F0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x44) = arg1;
}

/* Assembly between the functions: func_0017C9F8 (256 bytes), func_0017CAF8 (2488 bytes), func_0017D4B0 (760 bytes), func_0017D7A8 (808 bytes), func_0017DAD0 (64 bytes), func_0017DB10 (8 bytes) */

void func_0017DB18(void *arg0) {
    if (func_0017E770() == 0) {
        M2C_FIELD(arg0, s8 *, 0x7E) = 1;
    }
}
