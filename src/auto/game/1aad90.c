#include "auto/prelude.h"

extern s32 func_001AB1C0();
extern s32 func_00137AE0();
extern M2C_UNK D_003F6E30;

void func_001AAD90(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), &D_003F6E30, arg2);
}

void func_001AADF0(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), "S_750", arg2);
}

void func_001AAE50(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), "U_745", arg2);
}

void func_001AAEB0(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), "S_650", arg2);
}
