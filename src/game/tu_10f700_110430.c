#include "ps2/prelude.h"

extern s32 func_00101068(s32, s32, void *);
extern s32 D_0040F0E4;
extern void * D_0040F4C0;

void func_00110430(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x7E1) != 0) {
        func_00101068(D_0040F0E4, M2C_FIELD(D_0040F4C0, s32 *, 0xD540), arg0 + 0x700);
    }
}

void func_00110478(void *arg0, f32 fparg0) {
    if (M2C_FIELD(arg0, u8 *, 0x1664) != 0) {
        M2C_FIELD(arg0, f32 *, 0x700) = fparg0;
    }
}
