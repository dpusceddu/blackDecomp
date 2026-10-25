#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00123CE0();
extern s32 func_00122C80();
extern M2C_UNK D_0048F4E0;

s32 func_00122DF8(M2C_UNK *arg0) {
    M2C_FIELD(arg0, s8 *, 0x52E) = 0;
    func_00123CE0();
    func_00122C80(&D_0048F4E0);
    M2C_FIELD(arg0, s8 *, 0x52D) = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_122df8", func_00122E38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_122df8", func_00123020);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_122df8", func_001231C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_122df8", func_00123248);
