#include "include_asm.h"
#include "ps2/prelude.h"

#include "game/layouts/Recovered_FrontendLoadState.h"
#include "ps2/recovered_types.h"

s32 func_00106068(Recovered_FrontendLoadState *arg0) {
    M2C_FIELD(arg0, s64 *, 0x18) = 0;
    arg0->field_0 = 1;
    arg0->field_4 = 0;
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00106080);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00106200);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001063F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001064D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00106550);
