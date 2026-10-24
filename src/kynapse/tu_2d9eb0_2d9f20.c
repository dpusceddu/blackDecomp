/* Translation unit kynapse/tu_2d9eb0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_002DFEB0();
extern M2C_UNK D_00450C88;
extern M2C_UNK func_002D9EB0;
extern M2C_UNK * D_00450D98;
extern M2C_UNK D_003E3D38;

void func_002D9F20(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002DFEB0(&D_00450C88, "CActionTorsoRotate", &func_002D9EB0);
            return;
        }
        D_00450D98 = &D_003E3D38;
    }
}

/* Assembly between the functions: func_002D9F78 (136 bytes) */

void func_002DA000(void) {
    func_002D9F20(1, 0xFFFF);
}

void func_002DA020(void) {
    func_002D9F20(0, 0xFFFF);
}
