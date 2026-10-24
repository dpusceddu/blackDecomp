#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_001A2800(void *arg0) {
    s32 var_3;
    void *temp_2;
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0x38);
    var_3 = 0;
    if (M2C_FIELD(temp_4, u8 *, 0x38) == 0) {
        temp_2 = M2C_FIELD(temp_4, void **, 0x7C);
        var_3 = M2C_FIELD(temp_2, u8 *, 0x3A9) == M2C_FIELD(temp_2, u8 *, 0x3AA);
    }
    return var_3;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A2830);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A2968);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A2B70);
