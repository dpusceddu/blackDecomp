#include "ps2/prelude.h"

extern s32 func_001AB1C0(s32, s32, M2C_UNK *, s32, M2C_UNK *, s32);
extern s32 func_00137AE0(s32);
extern M2C_UNK D_003F6DE8;
extern M2C_UNK D_003F6DF0;
extern M2C_UNK D_003F6DF8;
extern M2C_UNK D_003F6E00;

void func_001AA7E8(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), &D_003F6DE8, arg2);
}

void func_001AA848(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), &D_003F6DF0, arg2);
}

void func_001AA8A8(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), &D_003F6DE8, arg2);
}

void func_001AA908(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), &D_003F6DF8, arg2);
}

void func_001AA968(s32 arg0, s32 arg1, s32 arg2) {
    func_001AB1C0(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), &D_003F6E00, arg2);
}

void func_001AA9C8(void) {

}

void func_001AA9D0(void) {

}
