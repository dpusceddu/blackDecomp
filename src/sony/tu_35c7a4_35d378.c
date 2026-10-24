#include "ps2/prelude.h"

extern s32 func_0035D3C8();
extern s32 func_00365F80();
extern void * D_003D6944;

s32 func_0035D378(s32 arg0) {
    return func_0035D3C8(arg0, (s32) func_00365F80);
}

void func_0035D398(void) {
    func_0035D378(D_003D6944);
}
