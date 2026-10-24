#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00165AE0();
extern s32 func_00165BC8();

void func_00163CC8(void *arg0, s32 arg1) {
    func_00165AE0();
    func_00165BC8(arg0, arg1);
}
