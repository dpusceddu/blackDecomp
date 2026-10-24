#include "ps2/prelude.h"

extern s32 func_0027D020();
extern s32 func_0010F730(s32);
extern s32 func_0027A7A8(s32);
extern s32 func_001AE938(void *, M2C_UNK, s32);
extern void * D_0040F4C0;

void func_00110610(s32 arg0) {
    func_0027D020();
    func_0010F730(arg0 + 0x7F0);
    func_0027A7A8(arg0 + 0x700);
    func_0027A7A8(arg0 + 0x750);
}

void * func_00110650(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x7E1) != 0) {
        return arg0 + 0x750;
    }
    return arg0 + 0x700;
}

void func_00110670(s32 arg0) {
    func_001AE938(D_0040F4C0, 1, arg0 + 0x700);
}
