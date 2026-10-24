#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0033AFB0();
extern s32 func_003398D8(s32, s32, s32, s32, s32, f32);
extern s32 func_0033B4C0(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0033AFB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0033B4C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0033B608);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0033B610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0033B680);

void func_0033B688(void *arg0) {
    func_0033AFB0();
    func_003398D8(M2C_FIELD(arg0, s32 *, 0x30), M2C_FIELD(arg0, s32 *, 0x34), M2C_FIELD(arg0, s32 *, 0x2C), M2C_FIELD(arg0, s32 *, 0x18), M2C_FIELD(arg0, s32 *, 0x28), M2C_FIELD(arg0, f32 *, 0x14));
}

void func_0033B6C8(void) {
    func_0033B4C0(1, 0xFFFF);
}

void func_0033B6E8(void) {
    func_0033B4C0(0, 0xFFFF);
}
