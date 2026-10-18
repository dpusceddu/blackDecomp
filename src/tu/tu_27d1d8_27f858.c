/* Translation unit tu_27d1d8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_0027F890();
extern s32 func_0027FA68(M2C_UNK, M2C_UNK);

void func_0027F858(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x28) != 0) {
        func_0027F890();
        M2C_FIELD(arg0, u8 *, 0x28) = 0U;
    }
}

/* Assembly between the functions: func_0027F890 (304 bytes) */

void func_0027F9C0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x24) = arg1;
}

/* Assembly between the functions: func_0027F9C8 (144 bytes), func_0027FA58 (16 bytes), func_0027FA68 (312 bytes) */

void func_0027FBA0(void) {
    func_0027FA68(1, 0xFFFF);
}
