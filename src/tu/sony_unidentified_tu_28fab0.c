/* Translation unit sony_unidentified/tu_28fab0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 D_00443630;
extern s32 func_0028FB08();
extern s32 func_0028FAB0();
extern s32 func_0035D398();
extern s32 func_00100218();

void func_0028FBB8(void) {
    if (D_00443630 == 0) {
        D_00443630 = 1;
        func_0028FB08();
    }
}

/* Assembly between the functions: func_0028FBD8 (1776 bytes) */

void func_002902C8(s32 arg0) {
    func_0028FAB0();
    func_0035D398();
    func_00100218(arg0);
}
