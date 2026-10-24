#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00129240(void *, s32, M2C_UNK);
extern void * D_0040F4D0;

s32 func_00142F50(void *arg0) {
    func_00143550();
    M2C_FIELD(arg0, s32 *, 8) = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00142F80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00143158);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001433E0);

void func_00143550(void *arg0) {
    s32 temp_5;

    temp_5 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_5 != 0) {
        func_00129240(D_0040F4D0, temp_5, 0);
        M2C_FIELD(arg0, s32 *, 4) = 0;
    }
}
