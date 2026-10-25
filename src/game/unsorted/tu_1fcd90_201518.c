#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001F1C08();
extern void func_00200F00(void *);

void func_00201518(s32 arg0) {
    func_001F1C08();
    func_00200F00(arg0 + 0x20);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90_201518", func_00201548);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90_201518", func_00201760);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90_201518", func_00201960);
