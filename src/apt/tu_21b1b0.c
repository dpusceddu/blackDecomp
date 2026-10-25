#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0021B1B0();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_21b1b0", func_0021B1B0);

s32 func_0021BAC0(s32 arg0, s32 arg1, s32 arg2) {
    return func_0021B1B0(arg0, arg1, 0, arg2);
}

void func_0021BAE0(void) {
    func_0021B1B0();
}
