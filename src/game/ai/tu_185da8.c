#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 * func_0018A678();
extern s32 func_00176F00();
extern void func_00186E68();
extern s32 func_00186988();
extern s32 func_00185FF0();
extern void func_00186218();

void func_00185DA8(void *arg0) {
    s32 *temp_17;

    temp_17 = func_0018A678(M2C_FIELD(arg0, s32 *, 0xA4) + 0x150);
    if (func_00176F00(M2C_FIELD(arg0, s32 *, 0xA4) + 0x1FCC) & 0xFF) {
        func_00186E68(arg0, temp_17);
    }
    func_00186988(arg0, temp_17);
    func_00185FF0(arg0, temp_17, M2C_FIELD(arg0, u8 *, 0x76) ^ 1);
    func_00186218(arg0, temp_17, M2C_FIELD(arg0, u8 *, 0x82) ^ 1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_185da8", func_00185E38);

s32 func_00185F00(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x70) != 0;
}

s32 func_00185F10(s32 arg0) {
    return arg0 + 0x90;
}

s32 func_00185F18(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x7C) != 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_185da8", func_00185F28);

s32 func_00185FE8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x7C);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_185da8", func_00185FF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_185da8", func_00186218);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_185da8", func_00186308);
