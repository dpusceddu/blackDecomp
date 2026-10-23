/* Translation unit tu_18d148 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern void func_00181AD0(void *arg0, s32 arg1);

u8 func_0018D608(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x15);
}

/* Assembly between the functions: func_0018D610 (72 bytes) */

void func_0018D658(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x15) == 0) {
        M2C_FIELD(arg0, u8 *, 0x15) = 1U;
        func_00181AD0(M2C_FIELD(arg0, s32 *, 0x1C) + 0xEC0, 9);
    }
}

void func_0018D698(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x18) = arg1;
    func_00181AD0(M2C_FIELD(arg0, s32 *, 0x1C) + 0xEC0, 0xB);
}

/* Assembly between the functions: func_0018D6C0 (56 bytes), func_0018D6F8 (56 bytes), func_0018D730 (56 bytes), func_0018D768 (56 bytes), func_0018D7A0 (120 bytes) */

void func_0018D818(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x50) & 0xEF) {
        M2C_FIELD(arg0, u8 *, 0x50) = 0x10U;
        func_00181AD0(M2C_FIELD(arg0, s32 *, 0x1C) + 0xEC0, 0xD);
    }
}

void func_0018D858(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x50) = (u8) ((M2C_FIELD(arg0, u8 *, 0x50) & 0xFE) | 2);
}
