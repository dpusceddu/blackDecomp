#include "include_asm.h"
#include "ps2/prelude.h"

extern void * D_003BFAE4;

void func_00252928(void *arg0) {
    M2C_FIELD(arg0, void **, 8) = (void *) D_003BFAE4;
    D_003BFAE4 = arg0;
}

void func_00252940(void *arg0) {
    M2C_FIELD(arg0, void **, 8) = (void *) D_003BFAE4;
    D_003BFAE4 = arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_251938_252928", func_00252958);
