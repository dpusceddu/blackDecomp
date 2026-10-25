#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/weapons/state.h"

extern s32 func_0015A938(void *arg0);

s32 func_00158078(void *arg0) {
    return BkWeaponReloadingPS2(arg0);
}

s32 func_00158088(void *arg0) {
    return ((BkWeaponControllerPS2*)arg0)->phase == 1;
}

s32 func_00158098(void *arg0) {
    s32 temp_3;
    s32 var_4;

    temp_3 = ((BkWeaponControllerPS2*)arg0)->phase;
    var_4 = 0;
    if ((temp_3 == 1) || (temp_3 == 8)) {
        var_4 = 1;
    }
    return var_4;
}

void func_001580C0(void *arg0) {
    func_0015A938(((BkWeaponControllerPS2*)arg0)->primary);
}

s16 func_001580E0(void *arg0) {
    return BkWeaponClipPS2(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1561f8_158078", func_001580F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1561f8_158078", func_001583D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1561f8_158078", func_00158668);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1561f8_158078", func_001588F0);
