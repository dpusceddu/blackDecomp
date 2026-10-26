#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193980();
extern s32 func_00193988();
extern s32 func_001825B0(void *);
extern s32 func_00185F00(void *);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1984f0", func_001984F0);

void func_00198568(void) {
    func_00193980();
}

void func_00198588(s32 *arg0) {
    func_00193988();
    func_001825B0(*arg0 + 0x810);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1984f0", func_001985B8);
s32 func_00198908(void **action) {
    u8 *owner = *action;
    if ((owner[0xD60] >> 4) & 1) {
        if (func_00185F00(owner + 0x90) == 0) goto eligible;
        if (M2C_FIELD(M2C_FIELD(*action, void **, 0x100), s32 *, 0x24) == 2) return 0;
eligible:
        return 1;
    }
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1984f0", func_00198968);
