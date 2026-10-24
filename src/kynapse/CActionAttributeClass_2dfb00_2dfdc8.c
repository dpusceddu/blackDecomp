/* Translation unit kynapse/CActionAttributeClass_2dfb00 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_0038B6B0();
extern M2C_UNK D_003E6D40;
extern s32 func_0038B840();
extern M2C_UNK D_003E6D28;
extern s32 D_003E6CE8;
extern s32 D_0049B008;

s32 func_002DFDC8(s32 arg0, s32 arg1, s32 arg2) {
    func_0038B6B0(arg0, arg1, arg2, 0, 0, 0);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E6D40;
    return arg0;
}

/* Assembly between the functions: func_002DFE08 (56 bytes), func_002DFE40 (112 bytes) */

void * func_002DFEB0(void *arg0, void *arg1, void *arg2) {
    func_0038B840((s32) arg0, (s32) arg1, (s32) arg2, 0, 0, 0);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E6D28;
    return arg0;
}

void func_002DFEF0(void) {
    D_003E6CE8 = 0;
}

void func_002DFF00(void) {
    D_0049B008 = 0;
}
