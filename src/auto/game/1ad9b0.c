#include "auto/prelude.h"

extern s32 func_001AB1C0();
extern s32 D_003BD190;
extern M2C_UNK D_003F6E00;

s32 func_001AD9B0(s32 arg0, s32 arg1, s32 arg2) {
    return func_001AB1C0(arg0, arg1, D_003BD190, arg0 + 0x60, (s32) "S_300", arg2);
}

s32 func_001AD9E0(s32 arg0, s32 arg1, s32 arg2) {
    return func_001AB1C0(arg0, arg1, D_003BD190, arg0 + 0x60, (s32) &D_003F6E00, arg2);
}

s32 func_001ADA10(s32 arg0, s32 arg1, s32 arg2) {
    return func_001AB1C0(arg0, arg1, D_003BD190, arg0 + 0x60, (s32) "S_106", arg2);
}

s32 func_001ADA40(s32 arg0, s32 arg1, s32 arg2) {
    return func_001AB1C0(arg0, arg1, D_003BD190, arg0 + 0x60, (s32) "S_107", arg2);
}

s32 func_001ADA70(s32 arg0, s32 arg1, s32 arg2) {
    return func_001AB1C0(arg0, arg1, D_003BD190, arg0 + 0x60, (s32) "???", arg2);
}
