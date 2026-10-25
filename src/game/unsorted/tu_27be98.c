#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0027C2A8(s8 *arg0, s32 arg1);
extern s32 func_0035CCD8();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027BE98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027BFC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027C088);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027C0B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027C0B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027C0D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027C0D8);

s32 func_0027C110(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x2011C) = arg1;
    return 1;
}


void func_0027C1A0(void) {

}


void func_0027C278(s8 *arg0) {
    func_0027C2A8(arg0, func_0035CCD8());
}
