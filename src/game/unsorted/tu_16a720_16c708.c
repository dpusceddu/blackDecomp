#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00169BF0();
extern s32 func_00169EB8();
extern s32 func_00273888();
extern void * D_0040F4D0;
extern M2C_UNK func_0016CD58;
extern s32 func_0016D1F8(M2C_UNK, M2C_UNK);

void func_0016C708(void) {
    func_00169BF0();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16c708", func_0016C728);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16c708", func_0016C9E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16c708", func_0016CB50);

s32 func_0016CCF0(void) {
    func_00169EB8();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16c708", func_0016CD10);

void func_0016CD18(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x11C) = 1;
    func_00273888(D_0040F4D0 + 0x4920, arg0 + 0x160, &func_0016CD58, arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16c708", func_0016CD58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16c708", func_0016CDC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16c708", func_0016CFF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16c708", func_0016D1F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16c708", func_0016D760);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16c708", func_0016D798);

void func_0016D7D0(void) {
    func_0016D1F8(1, 0xFFFF);
}
