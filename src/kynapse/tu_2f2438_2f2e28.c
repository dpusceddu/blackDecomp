/* Translation unit kynapse/tu_2f2438 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_002E7610();
extern M2C_UNK D_00452158;
extern M2C_UNK func_002F2438;
extern M2C_UNK * D_00452268;
extern M2C_UNK D_003E5E40;
extern s32 D_003EDA20;

void func_002F2E28(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E7610(&D_00452158, "CGraphManager", &func_002F2438, 0, 0, 0);
            return;
        }
        D_00452268 = &D_003E5E40;
    }
}

/* Assembly between the functions: func_002F2E88 (208 bytes), func_002F2F58 (152 bytes), func_002F2FF0 (248 bytes), func_002F30E8 (288 bytes), func_002F3208 (72 bytes), func_002F3250 (112 bytes), func_002F32C0 (216 bytes) */

void func_002F3398(void) {
    D_003EDA20 = 0;
}

void func_002F33A8(void) {
    func_002F2E28(1, 0xFFFF);
}

void func_002F33C8(void) {
    func_002F2E28(0, 0xFFFF);
}
