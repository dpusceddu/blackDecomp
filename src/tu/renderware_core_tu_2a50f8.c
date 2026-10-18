/* Translation unit renderware_core/tu_2a50f8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_002A71E0();
extern M2C_UNK D_00449540;

s32 func_002A53A8(s32 arg0) {
    func_002A71E0();
    return arg0;
}

/* Assembly between the functions: func_002A53D0 (80 bytes), func_002A5420 (296 bytes), func_002A5548 (64 bytes), func_002A5588 (48 bytes), func_002A55B8 (24 bytes), func_002A55D0 (8 bytes), func_002A55D8 (104 bytes), func_002A5640 (512 bytes), func_002A5840 (16 bytes), func_002A5850 (552 bytes), func_002A5A78 (24 bytes), func_002A5A90 (48 bytes) ... */

void * func_002A5B60(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) (M2C_FIELD(arg0, s32 *, 0xC) & 0xFFFDFFFC);
    return arg0;
}

/* Assembly between the functions: func_002A5B80 (24 bytes), func_002A5B98 (48 bytes), func_002A5BC8 (184 bytes), func_002A5C80 (104 bytes), func_002A5CE8 (808 bytes), func_002A6010 (816 bytes), func_002A6340 (672 bytes) */

M2C_UNK * func_002A65E0(void) {
    return &D_00449540;
}
