/* Translation unit kynapse/tu_2fcaa8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern char D_00407D58[];
const char rodata_00407D58[32] __asm__("D_00407D58") __attribute__((aligned(8))) = "CAccessWaysData" "\000" "Q24Kaim7CObject" "\000";
extern s32 func_002F35B0();
extern M2C_UNK D_00454670;
extern M2C_UNK func_002FCAA8;
extern M2C_UNK * D_00454780;
extern M2C_UNK D_003EC200;
extern M2C_UNK D_003EF368;

void func_002FD780(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002F35B0(&D_00454670, D_00407D58, &func_002FCAA8);
            return;
        }
        D_00454780 = &D_003EC200;
    }
}

void * func_002FD7D8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003EF368;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s16 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    return arg0;
}

/* Assembly between the functions: func_002FD800 (200 bytes), func_002FD8C8 (64 bytes), func_002FD908 (80 bytes) */

void func_002FD958(void) {
    func_002FD780(1, 0xFFFF);
}

void func_002FD978(void) {
    func_002FD780(0, 0xFFFF);
}
