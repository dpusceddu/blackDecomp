/* Translation unit tu_1f2ea8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_001F1E20();
extern M2C_UNK D_003F9558;
extern M2C_UNK D_003F9570;
extern M2C_UNK D_003F9580;

s32 func_001F2FF8(s32 arg0) {
    func_001F1E20(arg0, (s32) &D_003F9558);
    func_001F1E20(arg0, (s32) &D_003F9570);
    func_001F1E20(arg0, (s32) &D_003F9580);
    return 1;
}

/* Assembly between the functions: func_001F3048 (504 bytes), func_001F3240 (504 bytes), func_001F3438 (384 bytes) */

void func_001F35B8(void *arg0, f32 fparg0) {
    void *temp_2;

    temp_2 = arg0 + 0x98;
    M2C_FIELD(temp_2, f32 *, 4) = (f32) (M2C_FIELD(temp_2, f32 *, 4) * fparg0);
    M2C_FIELD(arg0, f32 *, 0x98) = (f32) (M2C_FIELD(arg0, f32 *, 0x98) * fparg0);
}
