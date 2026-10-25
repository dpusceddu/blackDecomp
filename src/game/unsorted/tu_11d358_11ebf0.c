#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0011D490();
extern s32 func_0011D430();

void func_0011EBF0(void) {
    func_0011D490();
}

s32 func_0011EC10(s32 arg0) {
    return func_0011D430(arg0, 5);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_11d358_11ebf0", func_0011EC30);
