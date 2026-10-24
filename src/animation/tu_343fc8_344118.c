#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00343FC8();
extern s32 func_00344050();
extern s32 func_003440B8();

s32 func_00344118(s32 arg0, s32 arg1, s32 arg2) {
    u8 sp[24];
    func_00343FC8(sp);
    func_00344050(sp, arg2);
    func_003440B8(arg0, arg1, sp);
    return arg0;
}
