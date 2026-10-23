/* Translation unit kynapse/tu_2d8138 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_002DFEB0();
extern M2C_UNK D_0044F9F0;
extern M2C_UNK func_002D8138;
extern M2C_UNK * D_0044FB00;
extern M2C_UNK D_003E3D38;

void func_002D81A8(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002DFEB0(&D_0044F9F0, "CActionSpeed", &func_002D8138);
            return;
        }
        D_0044FB00 = &D_003E3D38;
    }
}

/* Assembly between the functions: func_002D8200 (128 bytes) */

void func_002D8280(void) {
    func_002D81A8(1, 0xFFFF);
}

void func_002D82A0(void) {
    func_002D81A8(0, 0xFFFF);
}
