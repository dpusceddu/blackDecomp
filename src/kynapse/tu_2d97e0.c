#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_00450828;
extern M2C_UNK func_002D97E0;
extern M2C_UNK * D_00450938;
extern M2C_UNK D_003E4728;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D97E0);

void func_002D9880(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_00450828, "CEntityVisualAcuteness", &func_002D97E0);
            return;
        }
        D_00450938 = &D_003E4728;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D98D8);

void func_002D9970(void *arg0, f32 fparg0) {
    f32 var_f0;

    var_f0 = 0.0f;
    if (fparg0 < 0.0f) {
        /* Duplicate return node #1. Try simplifying control flow for better match */
        M2C_FIELD(arg0, f32 *, 8) = var_f0;
        return;
    }
    var_f0 = 360.0f;
    if (!(fparg0 > 360.0f)) {
        M2C_FIELD(arg0, f32 *, 8) = fparg0;
        return;
    }
    M2C_FIELD(arg0, f32 *, 8) = var_f0;
}

void func_002D99B8(void) {
    func_002D9880(1, 0xFFFF);
}

void func_002D99D8(void) {
    func_002D9880(0, 0xFFFF);
}
