/* Translation unit tu_270138 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_00270D80(M2C_UNK *, s32, s32);
extern M2C_UNK D_00440280;
extern s32 func_00270338(M2C_UNK *, s32);
extern s32 (*D_003BFB2C)();
extern s32 func_002710D8(M2C_UNK *);
extern s32 func_002CE010();

void func_00270138(s32 arg0, s32 arg1) {
    func_00270D80(&D_00440280, arg0, arg1);
}

void func_00270160(s32 arg0) {
    func_00270338(&D_00440280, arg0);
}

s32 func_00270188(s32 arg0, s32 arg1, s32 arg2) {
    func_002703D0(&D_00440280);
    return D_003BFB2C(arg0, arg1, arg2) != 0;
}

void func_002701E8(void *arg0) {
    s32 temp_2;
    s32 temp_6;
    u32 temp_5;

    temp_6 = M2C_FIELD(arg0, s32 *, 0x2F0);
    M2C_FIELD(arg0, s32 *, 0x2E0) = temp_6;
    temp_5 = 0x100000 - (temp_6 + M2C_FIELD(arg0, s32 *, 0x300));
    M2C_FIELD(arg0, u32 *, 0x2EC) = temp_5;
    temp_2 = (temp_5 >> 1) & 0xFFFFF800;
    M2C_FIELD(arg0, s32 *, 0x2DC) = temp_2;
    M2C_FIELD(arg0, s32 *, 0x2E4) = (s32) (temp_6 + temp_2);
}

/* Assembly between the functions: func_00270228 (272 bytes), func_00270338 (152 bytes) */

void func_002703D0(M2C_UNK *arg0) {
    func_002710D8(&D_00440280);
    func_002CE010();
    M2C_FIELD(arg0, s32 *, 0x2F8) = 0;
}
