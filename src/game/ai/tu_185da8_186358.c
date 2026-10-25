#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00185FF0(void *, s32, M2C_UNK);
extern s32 func_0018A678(s32);
extern s32 func_00185F00();
extern s32 func_00186218(void *, s32, M2C_UNK);
extern s32 func_00185F18();

void func_00186358(void *arg0) {
    func_00185FF0(arg0, func_0018A678(M2C_FIELD(arg0, s32 *, 0xA4) + 0x150), 1);
    func_00185F00(arg0);
}

void func_001863A0(void *arg0) {
    func_00186218(arg0, func_0018A678(M2C_FIELD(arg0, s32 *, 0xA4) + 0x150), 1);
    func_00185F18(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_185da8_186358", func_001863E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_185da8_186358", func_001865D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_185da8_186358", func_00186988);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_185da8_186358", func_00186B68);
