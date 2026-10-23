/* Translation unit kynapse/tu_2d7f90 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_002DFEB0();
extern M2C_UNK D_0044F8D8;
extern M2C_UNK func_002D7F90;
extern M2C_UNK * D_0044F9E8;
extern M2C_UNK D_003E3D38;

void func_002D8000(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002DFEB0(&D_0044F8D8, "CActionShoot", &func_002D7F90);
            return;
        }
        D_0044F9E8 = &D_003E3D38;
    }
}

/* Assembly between the functions: func_002D8058 (160 bytes) */

void func_002D80F8(void) {
    func_002D8000(1, 0xFFFF);
}

void func_002D8118(void) {
    func_002D8000(0, 0xFFFF);
}
