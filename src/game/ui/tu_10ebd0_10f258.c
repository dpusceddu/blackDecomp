#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001240B0(s32, M2C_UNK);
extern s32 func_0010F6D8(s32 *arg0);

void func_0010F258(void* unused) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_10ebd0_10f258", func_0010F260);

s32 func_0010F280(s32 arg0) {
    return arg0 + 0x18;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_10ebd0_10f258", func_0010F288);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_10ebd0_10f258", func_0010F470);

void func_0010F648(void *arg0) {
    func_001240B0(arg0 + 0xE0, 1);
    M2C_FIELD(arg0, s32 *, 0x788) = func_0010F6D8(arg0 + 0x18);
}

s32 func_0010F680(s32 *arg0) {
    s32 var_2;

    var_2 = 0;
    if (M2C_FIELD(arg0, s32 *, 0) == 0x26) {
        if (M2C_FIELD(arg0, s32 *, 4) != 0x778) {
            return 0;
        }
        var_2 = func_0010F6D8(arg0) == M2C_FIELD(arg0, s32 *, 0x770);
        /* Duplicate return node #5. Try simplifying control flow for better match */
        return var_2;
    }
    return var_2;
}
