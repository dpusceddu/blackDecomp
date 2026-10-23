/* Translation unit tu_142ed8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_00129240(void *, s32, M2C_UNK);
extern void * D_0040F4D0;

s32 func_00142F50(void *arg0) {
    func_00143550();
    M2C_FIELD(arg0, s32 *, 8) = 0;
    return 1;
}

/* Assembly between the functions: func_00142F80 (472 bytes), func_00143158 (648 bytes), func_001433E0 (368 bytes) */

void func_00143550(void *arg0) {
    s32 temp_5;

    temp_5 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_5 != 0) {
        func_00129240(D_0040F4D0, temp_5, 0);
        M2C_FIELD(arg0, s32 *, 4) = 0;
    }
}
