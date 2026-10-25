#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193988();
extern s32 func_00188148(void *, M2C_UNK);
extern s32 func_0019C7D8();
extern s32 func_00187FE0(s32, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_19c558", func_0019C558);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_19c558", func_0019C6E8);

void func_0019C760(s32 *arg0) {
    func_00193988();
    func_00188148(*arg0 + 0x290, 1);
}

void func_0019C798(s32 *arg0, s32 arg1) {
    if (arg1 == 3) {
        func_0019C7D8();
        func_00187FE0(*arg0 + 0x290, 0);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_19c558", func_0019C7D8);
