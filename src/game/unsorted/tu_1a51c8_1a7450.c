#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00347858();
extern void * func_00135550(void *);

void func_001A7450(void *arg0) {
    void *temp_4;

    if (M2C_FIELD(arg0, u8 *, 0xB9) != 0) {
        temp_4 = M2C_FIELD(arg0, void **, 0x54);
        if (M2C_FIELD(temp_4, s32 *, 4) != 0) {
            func_00347858(temp_4, arg0 + 0x10);
            M2C_FIELD(arg0, u8 *, 0xB9) = 0U;
        }
    }
}

void func_001A7498(void **arg0) {
    void *temp_3;

    temp_3 = func_00135550(*arg0);
    if ((*arg0 == NULL) || (temp_3 == NULL)) {
        func_001A7450(arg0);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A7528);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A7660);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A76E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A77C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A7E58);
