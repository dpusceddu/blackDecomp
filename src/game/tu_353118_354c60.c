#include "include_asm.h"
#include "ps2/prelude.h"

void func_00354C60(s32 arg0, void *arg1, void *arg2) {
    M2C_FIELD(arg1, void **, 0x28) = arg2;
    M2C_FIELD(arg1, void **, 0x24) = (void *) M2C_FIELD(arg2, void **, 0x24);
    M2C_FIELD(arg2, void **, 0x24) = arg1;
    M2C_FIELD(M2C_FIELD(arg1, void **, 0x24), void **, 0x28) = arg1;
}

void func_00354C80(s32 arg0, void *arg1) {
    M2C_FIELD(M2C_FIELD(arg1, void **, 0x24), void **, 0x28) = (void *) M2C_FIELD(arg1, void **, 0x28);
    M2C_FIELD(M2C_FIELD(arg1, void **, 0x28), void **, 0x24) = (void *) M2C_FIELD(arg1, void **, 0x24);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00354CA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00354CF0);
