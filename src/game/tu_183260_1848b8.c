/* Translation unit tu_183260 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_00175F50();
extern void * D_0040F4D4;

s32 func_001848B8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4);
}

/* Assembly between the functions: func_001848C0 (280 bytes), func_001849D8 (360 bytes), func_00184B40 (464 bytes), func_00184D10 (104 bytes), func_00184D78 (104 bytes), func_00184DE0 (1000 bytes), func_001851C8 (336 bytes) */

s32 func_00185318(s32 arg0, s32 arg1, s32 arg2) {
    return func_00175F50((s32) (D_0040F4D4 + 0xFA0), arg1, arg2, 0x221, M2C_FIELD(M2C_FIELD(arg0, u32 *, 0), s32 *, 0x7C), 1);
}
