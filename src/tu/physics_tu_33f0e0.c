/* Translation unit physics/tu_33f0e0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_0033F0E0(M2C_UNK, M2C_UNK);

void func_0033F228(void) {

}

/* Assembly between the functions: func_0033F230 (24 bytes), func_0033F248 (48 bytes), func_0033F278 (80 bytes) */

s32 func_0033F2C8(void) {
    return 1;
}

s32 func_0033F2D0(void *arg0, s32 arg1, s32 arg2, void *arg3) {
    M2C_FIELD(arg3, s32 *, 0x130) = 0;
    M2C_FIELD(arg3, s128 *, 0x120) = (s128) M2C_FIELD(arg0, s128 *, 0x30);
    return 1;
}

void func_0033F2E8(void) {
    func_0033F0E0(1, 0xFFFF);
}

void func_0033F308(void) {
    func_0033F0E0(0, 0xFFFF);
}
