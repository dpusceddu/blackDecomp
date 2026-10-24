/* Translation unit kynapse/tu_2f4390 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_002E4D88();
extern M2C_UNK D_004524A0;
extern M2C_UNK * D_004525B0;
extern M2C_UNK D_003E00F8;
extern s32 func_002E41D8();
extern M2C_UNK D_003EE090;

void func_002F49F0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4D88(&D_004524A0, "CPathObject", 0, 0);
            return;
        }
        D_004525B0 = &D_003E00F8;
    }
}

void * func_002F4A48(void *arg0) {
    func_002E41D8();
    M2C_FIELD(arg0, s32 *, 0x6C) = 0x19;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003EE090;
    M2C_FIELD(arg0, s32 *, 0x60) = 0;
    M2C_FIELD(arg0, s32 *, 0x64) = 0;
    M2C_FIELD(arg0, s32 *, 0x68) = 0;
    return arg0;
}

/* Assembly between the functions: func_002F4A90 (192 bytes), func_002F4B50 (48 bytes) */

void func_002F4B80(void) {
    func_002F49F0(1, 0xFFFF);
}

void func_002F4BA0(void) {
    func_002F49F0(0, 0xFFFF);
}
