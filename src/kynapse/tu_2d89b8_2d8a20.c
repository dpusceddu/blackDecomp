/* Translation unit kynapse/tu_2d89b8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_0044FE50;
extern M2C_UNK func_002D89B8;
extern M2C_UNK * D_0044FF60;
extern M2C_UNK D_003E4728;

void func_002D8A20(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_0044FE50, "CEntityGunPosition", &func_002D89B8);
            return;
        }
        D_0044FF60 = &D_003E4728;
    }
}

/* Assembly between the functions: func_002D8A78 (144 bytes) */

void func_002D8B08(void) {
    func_002D8A20(1, 0xFFFF);
}

void func_002D8B28(void) {
    func_002D8A20(0, 0xFFFF);
}
