#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00188F10();
extern s32 func_00189740(s32, void *, M2C_UNK);
extern void * D_0040F4D0;
extern s32 func_0018A8D8(s32, s32, s32);
extern s32 func_001792B0(s32);
extern s32 D_0040F4D4;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_18a5c0", func_0018A5C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_18a5c0", func_0018A678);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_18a5c0", func_0018A6F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_18a5c0", func_0018A790);

void func_0018A890(s32 arg0) {
    if (func_00188F10() == 0) {
        func_00189740(arg0, D_0040F4D0 + 0x30, 1);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_18a5c0", func_0018A8D8);

void func_0018A9C8(s32 arg0, s32 arg1, s32 arg2) {
    func_0018A8D8(arg0, func_001792B0(D_0040F4D4 + 0xFA8), arg2);
}
