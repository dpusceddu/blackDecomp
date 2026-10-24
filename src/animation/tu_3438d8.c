#include "include_asm.h"
#include "ps2/prelude.h"

extern void * func_00344020();

void func_003438D8(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003438E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00343A30);

void * func_00343BC0(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2) {
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) (M2C_FIELD(arg0, f32 *, 0x10) * fparg0);
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) (M2C_FIELD(arg0, f32 *, 0x14) * fparg1);
    M2C_FIELD(arg0, f32 *, 0x18) = (f32) (M2C_FIELD(arg0, f32 *, 0x18) * fparg2);
    return arg0;
}

void * func_00343BF0(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) -M2C_FIELD(arg0, f32 *, 0x10);
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) -M2C_FIELD(arg0, f32 *, 0x14);
    M2C_FIELD(arg0, f32 *, 0x18) = (f32) -M2C_FIELD(arg0, f32 *, 0x18);
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) -M2C_FIELD(arg0, f32 *, 0xC);
    return arg0;
}

s32 func_00343C28(s32 arg0, s32 arg1) {
    if (arg0 != 0) {
        if (arg1 != 0) {
            func_00344020();
        }
    }
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00343C60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00343E08);
