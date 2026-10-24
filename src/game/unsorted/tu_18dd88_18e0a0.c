#include "include_asm.h"
#include "ps2/prelude.h"

f32 func_0018E0A0(void *arg0) {
    f32 var_f0;
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 4);
    if ((temp_3 >= 0x20) || (var_f0 = 0.9f, ((temp_3 < 0x1D) != 0))) {
        var_f0 = 0.0f;
    }
    return var_f0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018E0D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018E0F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018E110);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018E130);
