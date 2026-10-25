#include "include_asm.h"
#include "ps2/prelude.h"

extern void * D_003BFAE8;

void func_002529E0(void *arg0) {
    M2C_FIELD(arg0, void **, 8) = (void *) D_003BFAE8;
    D_003BFAE8 = arg0;
}

void func_002529F8(void *arg0) {
    M2C_FIELD(arg0, void **, 8) = (void *) D_003BFAE8;
    D_003BFAE8 = arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_251938_2529e0", func_00252A10);
