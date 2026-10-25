#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00288A38();
extern s32 func_00287120();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288488", func_00288488);

s32 func_002886D0(s32 arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 8) + arg0;
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + arg0);
    M2C_FIELD(arg0, s32 *, 8) = temp_3;
    func_00288A38(temp_3);
    return func_00287120(M2C_FIELD(arg0, s32 *, 4));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288488", func_00288718);
