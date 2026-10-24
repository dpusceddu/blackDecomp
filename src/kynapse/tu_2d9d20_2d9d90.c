/* Translation unit kynapse/tu_2d9d20 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_002DFEB0();
extern M2C_UNK D_00450B70;
extern M2C_UNK func_002D9D20;
extern M2C_UNK * D_00450C80;
extern M2C_UNK D_003E3D38;

void func_002D9D90(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002DFEB0(&D_00450B70, "CActionHeadRotate", &func_002D9D20);
            return;
        }
        D_00450C80 = &D_003E3D38;
    }
}

/* Assembly between the functions: func_002D9DE8 (136 bytes) */

void func_002D9E70(void) {
    func_002D9D90(1, 0xFFFF);
}

void func_002D9E90(void) {
    func_002D9D90(0, 0xFFFF);
}
