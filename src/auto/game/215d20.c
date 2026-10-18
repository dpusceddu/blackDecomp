#include "auto/prelude.h"

extern s32 func_00275260();
extern s32 func_0020DE78();
extern M2C_UNK D_004924B0;
extern s32 func_00215BE8();

void func_00215D20(s32 arg0) {
    u8 sp[56];
    func_00275260(arg0 + 0x78, sp, 0x20);
    func_0020DE78(&D_004924B0, sp);
    func_00215BE8(arg0);
}
