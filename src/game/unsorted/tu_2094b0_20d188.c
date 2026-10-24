#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00275068();
extern s32 func_00275090();

s32 func_0020D188(s32 arg0, s32 arg1) {
    return func_00275068(arg0, arg1, 4);
}

void func_0020D1A8(void) {
    func_00275090();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0020D1C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0020D880);
