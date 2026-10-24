#include "ps2/prelude.h"

extern s32 func_00118088();
extern s32 func_00116FC8();

s32 func_00116F68(s32 arg0, s32 arg1) {
    func_00118088();
    func_00116FC8(arg0, arg1);
    return 1;
}

void func_00116FA8(void) {
    func_00116FC8();
}
