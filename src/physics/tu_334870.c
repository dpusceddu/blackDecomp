#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00334870();
extern s32 func_00334870(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_334870", func_00334870);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_334870", func_003349B8);

void * func_003349C0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = 0x10;
    M2C_FIELD(arg0, s32 *, 0) = (s32) ((arg1 * 0x60) + 0x40);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_334870", func_003349E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_334870", func_00334A48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_334870", func_00334A50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_334870", func_00334B18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_334870", func_00334B48);

void func_00334B58(void) {
    func_00334870(1, 0xFFFF);
}

void func_00334B78(void) {
    func_00334870(0, 0xFFFF);
}
