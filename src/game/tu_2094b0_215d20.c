#include "auto/prelude.h"

extern s32 func_00275260();
extern s32 func_0020DE78();
extern M2C_UNK D_004924B0;
extern s32 func_00215BE8();
extern s32 func_0020DE28();
extern s32 D_004924B0;
extern s32 func_0035D1A0(M2C_UNK *, s32, M2C_UNK);
extern M2C_UNK D_003BE860;

void func_00215D20(s32 arg0) {
    u8 sp[56];
    func_00275260(arg0 + 0x78, sp, 0x20);
    func_0020DE78(&D_004924B0, sp);
    func_00215BE8(arg0);
}

void func_00215D68(s32 arg0, s32 arg1) {
    func_0020DE28(&D_004924B0);
    func_0035D1A0(&D_003BE860, arg1, 0x3C);
}
