/* Translation unit tu_18a5c0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_00188F10();
extern s32 func_00189740(s32, void *, M2C_UNK);
extern void * D_0040F4D0;
extern s32 func_0018A8D8(s32, s32, s32);
extern s32 func_001792B0(s32);
extern s32 D_0040F4D4;

void func_0018A890(s32 arg0) {
    if (func_00188F10() == 0) {
        func_00189740(arg0, D_0040F4D0 + 0x30, 1);
    }
}

/* Assembly between the functions: func_0018A8D8 (240 bytes) */

void func_0018A9C8(s32 arg0, s32 arg1, s32 arg2) {
    func_0018A8D8(arg0, func_001792B0(D_0040F4D4 + 0xFA8), arg2);
}
