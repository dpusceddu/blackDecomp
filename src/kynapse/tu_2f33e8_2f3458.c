/* Translation unit kynapse/tu_2f33e8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_002E7400();
extern M2C_UNK D_00452270;
extern M2C_UNK func_002F33E8;
extern M2C_UNK * D_00452380;
extern M2C_UNK D_003EA7E8;

void func_002F3458(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E7400(&D_00452270, "CGraphWrapper", &func_002F33E8, 0);
            return;
        }
        D_00452380 = &D_003EA7E8;
    }
}

/* Assembly between the functions: func_002F34B0 (112 bytes), func_002F3520 (16 bytes), func_002F3530 (64 bytes) */

void func_002F3570(void) {
    func_002F3458(1, 0xFFFF);
}

void func_002F3590(void) {
    func_002F3458(0, 0xFFFF);
}
