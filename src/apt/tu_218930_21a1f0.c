/* Translation unit apt/tu_218930 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_0021A130();
extern s32 D_0043DF50;
extern void * D_0043DF68;

void func_0021A1F0(void) {
    func_0021A130();
}

/* Assembly between the functions: func_0021A210 (8 bytes), func_0021A218 (416 bytes), func_0021A3B8 (200 bytes), func_0021A480 (864 bytes), func_0021A7E0 (656 bytes), func_0021AA70 (40 bytes), func_0021AA98 (704 bytes) */

void func_0021AD58(void) {
    if ((D_0043DF50 == 0) && (D_0043DF68 != NULL)) {
        M2C_FIELD(D_0043DF68, s32 *, 0x24) = 0;
    }
}
