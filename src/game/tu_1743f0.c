#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00165AE0();
extern s32 func_00165BC8(s32, s32);

void func_001743F0(s32 arg0, s32 arg1) {
    func_00165AE0();
    func_00165BC8(arg0, arg1);
}
