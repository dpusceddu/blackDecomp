#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0011D430();
extern s32 func_00382348();
extern M2C_UNK D_0040EAF0;

s32 func_0011E488(s32 arg0) {
    func_0011D430(arg0, 2);
    return func_00382348((s32) &D_0040EAF0, 0x02B9D6F8);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0011E4B8);
