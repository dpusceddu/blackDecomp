/* Translation unit kynapse/tu_2d9190 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_004503C8;
extern M2C_UNK func_002D9190;
extern M2C_UNK * D_004504D8;
extern M2C_UNK D_003E4728;

void func_002D9228(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_004503C8, "CEntityLength", &func_002D9190);
            return;
        }
        D_004504D8 = &D_003E4728;
    }
}

/* Assembly between the functions: func_002D9280 (112 bytes) */

void func_002D92F0(void) {
    func_002D9228(1, 0xFFFF);
}

void func_002D9310(void) {
    func_002D9228(0, 0xFFFF);
}
