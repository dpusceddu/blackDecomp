#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 (*D_00451238)();

void func_00384388(s32 arg0, s32 arg1) {
    D_00451238(arg1);
}
