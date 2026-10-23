/* Translation unit kynapse/tu_2eef88 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_002F35B0();
extern M2C_UNK D_00451658;
extern M2C_UNK func_002EEF88;
extern M2C_UNK * D_00451768;
extern M2C_UNK D_003EC200;
extern M2C_UNK * D_003EC1C8;
extern s32 (*D_003C87E0)();
extern M2C_UNK * D_003E0040;

void func_002F09A8(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002F35B0(&D_00451658, "CFindNearestData", &func_002EEF88);
            return;
        }
        D_00451768 = &D_003EC200;
    }
}

/* Assembly between the functions: func_002F0A00 (48 bytes) */

void func_002F0D68(void) {
    func_002F09A8(1, 0xFFFF);
}

void func_002F0D88(void) {
    func_002F09A8(0, 0xFFFF);
}
