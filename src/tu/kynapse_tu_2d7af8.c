/* Translation unit kynapse/tu_2d7af8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_002DFEB0();
extern M2C_UNK D_0044F590;
extern M2C_UNK func_002D7AF8;
extern M2C_UNK * D_0044F6A0;
extern M2C_UNK D_003E3D38;

void func_002D7B68(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002DFEB0(&D_0044F590, "CActionCrouch", &func_002D7AF8);
            return;
        }
        D_0044F6A0 = &D_003E3D38;
    }
}

/* Assembly between the functions: func_002D7BC0 (128 bytes) */

void func_002D7C40(void) {
    func_002D7B68(1, 0xFFFF);
}

void func_002D7C60(void) {
    func_002D7B68(0, 0xFFFF);
}
