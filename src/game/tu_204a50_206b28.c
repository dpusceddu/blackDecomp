#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002050B0();

void func_00206B28(void) {

}

s32 func_00206B30(void) {
    func_002050B0();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00206B50);
