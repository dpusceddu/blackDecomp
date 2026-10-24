#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00173640(f32 *, f32);

s32 func_00173658(f32 *arg0) {
    return func_00173640(arg0, 0.0f);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00173678);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00173690);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001736A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001736B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001736B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00173748);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001739E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00173D38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00173D80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00173E18);

#include "ps2/recovered_types.h"
extern M2C_UNK D_003F6228;
extern s32 func_001739E0(void *, s32, s32);

void func_00173E30(void *arg0, s32 arg1, f32 fparg0) {
    s32 var_6;

    var_6 = 0;
    if ((arg1 != 0) && (M2C_FIELD(arg0, s32 *, 0x14) != arg1)) {
        if (fparg0 == 0.0f) {
            M2C_FIELD(arg0, f32 *, 0x1C) = (f32) (M2C_FIELD(arg0, f32 *, 0x18) * M2C_FIELD(((arg1 * 4) + ((s32) &D_003F6228)), f32 *, 0));
        }
        M2C_FIELD(arg0, s32 *, 0x14) = arg1;
        var_6 = 1;
    }
    if (fparg0 > 0.0f) {
        M2C_FIELD(arg0, f32 *, 0x1C) = fparg0;
        var_6 = 1;
        M2C_FIELD(arg0, f32 *, 0x18) = (f32) (fparg0 / M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x14) * 4) + ((s32) &D_003F6228)), f32 *, 0));
    }
    if (var_6 != 0) {
        func_001739E0(arg0, arg1, var_6);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00173EE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00173F18);
