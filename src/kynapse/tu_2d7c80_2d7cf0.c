/* Translation unit kynapse/tu_2d7c80 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_002DFEB0();
extern M2C_UNK D_0044F6A8;
extern M2C_UNK func_002D7C80;
extern M2C_UNK * D_0044F7B8;
extern M2C_UNK D_003E3D38;

void func_002D7CF0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002DFEB0(&D_0044F6A8, "CActionJump", &func_002D7C80);
            return;
        }
        D_0044F7B8 = &D_003E3D38;
    }
}

/* Assembly between the functions: func_002D7D48 (128 bytes) */

void func_002D7DC8(void) {
    func_002D7CF0(1, 0xFFFF);
}

void func_002D7DE8(void) {
    func_002D7CF0(0, 0xFFFF);
}
