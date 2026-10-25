#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00400A08[];
const char rodata_00400A08[104] __asm__("D_00400A08") __attribute__((aligned(8))) = "%d" "\000\000\000\000\000\000" "RawData" "\000" "Graph" "\000\000\000" "AdditionalData" "\000\000" "CFindNearestData" "\000\000\000\000\000\000\000\000" "CAstarData" "\000\000\000\000\000\000" "UpdateWithPathObjects" "\000\000\000";
extern s32 func_0035D728();
extern s32 func_00288EF8();

s32 func_00288D08(s32 arg0, void *arg1) {
    return M2C_FIELD(arg1, s32 *, 4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_288d08", func_00288D10);

s32 func_00288E00(s32 arg0, s32 arg1) {
    s32 *temp_2;
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x20);
    temp_2 = (temp_3 * 4) + M2C_FIELD(arg0, s32 *, 0x18);
    *temp_2 = arg1;
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) (temp_3 + 1);
    return (s32) temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_288d08", func_00288E20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_288d08", func_00288E28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_288d08", func_00288EF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_288d08", func_00288FB0);

M2C_UNK *** func_00289028(M2C_UNK ***arg0, M2C_UNK ***arg1, M2C_UNK *arg2, M2C_UNK *arg3) {
    u8 sp[8];
    func_0035D728(sp, D_00400A08, arg3);
    func_00288EF8(arg0, arg1, arg2, sp);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_288d08", func_00289090);
