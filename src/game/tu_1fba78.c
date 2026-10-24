#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0035D728(void *, M2C_UNK *, s32);
extern M2C_UNK D_003F9598;
extern s32 func_00275260(void *, s32, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FBA78);

void func_001FBB40(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FBB48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FBD90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FC188);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FC280);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FC320);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FC400);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001FC558(void *, s32, s32);

s32 func_001FC490(void *arg0) {
    f32 var_f1;

    var_f1 = M2C_FIELD(arg0, f32 *, 0x15C) / M2C_FIELD(arg0, f32 *, 0x158);
    if (var_f1 > 1.0f) {
        var_f1 = 1.0f;
    }
    return func_001FC558(arg0, (s32) ((f32) M2C_FIELD(arg0, u16 *, 0x144) * (1.0f - var_f1)) & 0xFFFF, (s32) M2C_FIELD(arg0, u16 *, 0x146));
}

void func_001FC4F8(void) {

}

void func_001FC500(void) {

}

void func_001FC508(s32 arg0, s32 arg1) {
    void *temp_16;

    temp_16 = arg0 + 0x16C;
    func_0035D728(temp_16, &D_003F9598, arg1 & 0xFFFF);
    func_00275260(temp_16, arg0 + 0x17C, 4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FC558);
