#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 D_003D881C;
extern void ** func_00292088();
extern s32 func_0035E828();
extern M2C_UNK D_0040BEA0;
extern s32 func_00107D48();
extern M2C_UNK D_0040BE88;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036F978);

s32 func_0036F9B0(s32 arg0) {
    s32 temp_2;

    temp_2 = D_003D881C;
    D_003D881C = arg0;
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036F9C0);

void * func_0036FA00(void) {
    return *func_00292088();
}

void * func_0036FA20(void) {
    void *temp_3;

    temp_3 = *func_00292088();
    M2C_FIELD(temp_3, s32 *, 0x14) = 1;
    M2C_FIELD(temp_3, s64 *, 0x20) = (s64) (M2C_FIELD(temp_3, s64 *, 0x20) + 1);
    return temp_3;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036FA58);

void func_0036FA80(void) {
    func_0035E828();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036FAA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036FB10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036FBA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036FC68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036FC98);

s32 func_0036FF88(void **arg0) {
    return *M2C_FIELD(*arg0, s32 *(**)(), 4)();
}

s32 func_0036FFB0(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_0040BEA0;
    M2C_FIELD(arg0, u32 *, 0) = &D_0040BEA0;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}

M2C_UNK ** func_0036FFE0(M2C_UNK **arg0) {
    *arg0 = &D_0040BE88;
    return arg0;
}
