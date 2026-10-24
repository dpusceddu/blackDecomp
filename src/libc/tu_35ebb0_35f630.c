#include "ps2/prelude.h"

extern void * D_003D6944;
extern void func_0035EBB0(void *);
extern s32 func_00364538(void *, s32, s32);
extern void func_0035EC10(void *);

s32 func_0035F630(void) {
    s32 temp_3;

    temp_3 = (M2C_FIELD(D_003D6944, s32 *, 0x58) * 0x41C64E6D) + 0x3039;
    M2C_FIELD(D_003D6944, s32 *, 0x58) = temp_3;
    return temp_3 & 0x7FFFFFFF;
}

s32 func_0035F660(s32 arg0, s32 arg1) {
    s32 temp_17;

    func_0035EBB0(D_003D6944);
    temp_17 = func_00364538(D_003D6944, arg0, arg1);
    func_0035EC10(D_003D6944);
    return temp_17;
}
