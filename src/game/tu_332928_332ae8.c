/* Translation unit tu_332928 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_00332928();
extern s32 func_00332928(M2C_UNK, M2C_UNK);

void * func_00332AE8(void **arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_4;

    temp_4 = *arg0;
    if (temp_4 != NULL) {
        M2C_FIELD(temp_4, s32 *, 0) = 0;
        M2C_FIELD(temp_4, s32 *, 0x54) = 0;
        M2C_FIELD(temp_4, s32 *, 0x58) = 0;
        M2C_FIELD(temp_4, s32 *, 0x5C) = 0;
    }
    M2C_FIELD(temp_4, s32 *, 0) = arg2;
    M2C_FIELD(temp_4, s32 *, 0x54) = arg1;
    M2C_FIELD(temp_4, s32 *, 0x5C) = arg3;
    M2C_FIELD(temp_4, s32 *, 0x50) = 0;
    return temp_4;
}

/* Assembly between the functions: func_00332B20 (8 bytes) */

void func_00332B28(void) {
    func_00332928(1, 0xFFFF);
}

void func_00332B48(void) {
    func_00332928(0, 0xFFFF);
}
