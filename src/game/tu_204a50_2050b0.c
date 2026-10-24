/* Translation unit tu_204a50 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_00204F00();
extern s32 func_00103818(void *);
extern void * D_0040F0E0;

s32 func_002050B0(void) {
    return 1;
}

/* Assembly between the functions: func_002050B8 (184 bytes) */

s32 func_00205170(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    return 1;
}

/* Assembly between the functions: func_00205180 (144 bytes), func_00205210 (136 bytes), func_00205298 (8 bytes), func_002052A0 (288 bytes) */

void func_002053C0(void) {
    func_00204F00();
}

/* Assembly between the functions: func_002053E0 (952 bytes), func_00205798 (112 bytes) */

s32 func_00205808(void) {
    func_00103818(D_0040F0E0);
    return 1;
}
