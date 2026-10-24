#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_00135BC0();

void func_00135B80(void *arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x38C);
    M2C_FIELD(arg0, s32 *, 0x38C) = arg1;
    if (arg1 != 0) {
        if (temp_2 == 0) {
            func_00135BC0();
        }
        M2C_FIELD(arg0, s64 *, 0) = 0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00135BC0);
