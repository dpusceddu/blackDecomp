#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00107D48();

void func_00100230(s32 arg0, s32 arg1) {
    if (arg1 & 1) {
        func_00107D48(arg0);
    }
}
