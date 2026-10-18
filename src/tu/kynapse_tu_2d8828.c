/* Translation unit kynapse/tu_2d8828 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_0044FD38;
extern M2C_UNK func_002D8828;
extern M2C_UNK * D_0044FE48;
extern M2C_UNK D_003E4728;

void func_002D8890(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_0044FD38, "CEntityEyePosition", &func_002D8828);
            return;
        }
        D_0044FE48 = &D_003E4728;
    }
}

/* Assembly between the functions: func_002D88E8 (144 bytes) */

void func_002D8978(void) {
    func_002D8890(1, 0xFFFF);
}

void func_002D8998(void) {
    func_002D8890(0, 0xFFFF);
}
