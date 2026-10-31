#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_001084A8(void*, s32, s16);
extern void* D_0040F4C4;
extern s32 func_001438E8(s32);
extern s32 D_0040F540;

void func_0020AFF8(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x36E8) != 0) {
        func_001084A8(D_0040F4C4, 7, 0xC);
        M2C_FIELD(arg0, s32 *, 0x36E8) = 0;
    }
    M2C_FIELD(arg0, s32 *, 0x3924) = 0;
    func_001438E8(D_0040F540);
}

extern void func_0010BBB0(void*);
extern void* D_0040F4F0;

void func_0020B048(void* arg0) {
    if (M2C_FIELD(arg0, s32*, 0x36C8) != 0) {
        func_001084A8(D_0040F4C4, 7, 4);
        M2C_FIELD(arg0, s32*, 0x36C8) = 0;
    }
    if (M2C_FIELD(arg0, s32*, 0x36E4) != 0) {
        func_001084A8(D_0040F4C4, 7, 0xB);
        M2C_FIELD(arg0, s32*, 0x36E4) = 0;
    }
    func_0010BBB0(D_0040F4F0);
    M2C_FIELD(arg0, s32*, 0x37A4) = 0x38;
}
