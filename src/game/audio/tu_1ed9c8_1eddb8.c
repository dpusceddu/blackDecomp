#include "include_asm.h"
#include "ps2/prelude.h"

extern void * D_0040F4D0;
extern s32 func_001EDD80();

void func_001EDDB8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 2;
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) (M2C_FIELD(D_0040F4D0, f32 *, 0x20) + M2C_FIELD(arg0, f32 *, 0x38));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EDDE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EDE98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EE0B0);

void func_001EE150(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EE158);

void func_001EE270(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EE278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EE298);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EE540);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EE5E0);

void func_001EE670(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EE678);

void func_001EE850(void *arg0) {
    f32 temp_f1;

    func_001EDD80();
    temp_f1 = M2C_FIELD(arg0, f32 *, 4);
    M2C_FIELD(arg0, f32 *, 8) = temp_f1;
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) (M2C_FIELD(arg0, f32 *, 0x20) / temp_f1);
}
