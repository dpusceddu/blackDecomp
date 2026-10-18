/* Translation unit tu_1c22a0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 D_003BD1DC;
extern s32 func_001C4628(M2C_UNK *);
extern M2C_UNK D_004173E0;
extern void * D_0040F4C0;
extern s32 func_001AE538();

s32 func_001C3E08(void) {
    return 1;
}

/* Assembly between the functions: func_001C3E10 (800 bytes) */

void func_001C4130(s32 arg0) {
    D_003BD1DC = (arg0 != 0) ? 0 : 0x200;
}

/* Assembly between the functions: func_001C4148 (136 bytes), func_001C41D0 (544 bytes), func_001C43F0 (464 bytes) */

void func_001C45C0(void) {
    func_001C4628(&D_004173E0);
}

/* Assembly between the functions: func_001C45E0 (72 bytes), func_001C4628 (920 bytes), func_001C49C0 (32 bytes), func_001C49E0 (800 bytes) */

void func_001C4D00(void) {
    func_001C4F08(D_0040F4C0);
}

/* Assembly between the functions: func_001C4D28 (480 bytes) */

void func_001C4F08(void *arg0, u32 arg1) {
    M2C_FIELD(arg0, u32 *, 0xD5F0) = arg1;
    if (arg1 < (u32) M2C_FIELD(arg0, u32 *, 0xD5F4)) {
        M2C_FIELD(arg0, u32 *, 0xD5F4) = arg1;
    }
}

/* Assembly between the functions: func_001C4F30 (128 bytes), func_001C4FB0 (304 bytes) */

void func_001C50E0(void) {
    func_001AE538();
}
