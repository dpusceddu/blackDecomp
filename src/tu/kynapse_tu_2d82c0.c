/* Translation unit kynapse/tu_2d82c0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_002DFEB0();
extern M2C_UNK D_0044FB08;
extern M2C_UNK func_002D82C0;
extern M2C_UNK * D_0044FC18;
extern M2C_UNK D_003E3D38;

void func_002D8330(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002DFEB0(&D_0044FB08, "CActionSteering", &func_002D82C0);
            return;
        }
        D_0044FC18 = &D_003E3D38;
    }
}

/* Assembly between the functions: func_002D8388 (128 bytes) */

void func_002D8408(void) {
    func_002D8330(1, 0xFFFF);
}

void func_002D8428(void) {
    func_002D8330(0, 0xFFFF);
}
