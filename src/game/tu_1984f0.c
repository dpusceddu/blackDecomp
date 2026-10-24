#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193980();
extern s32 func_00193988();
extern s32 func_001825B0(void *);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001984F0);

void func_00198568(void) {
    func_00193980();
}

void func_00198588(s32 *arg0) {
    func_00193988();
    func_001825B0(*arg0 + 0x810);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001985B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00198908);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00198968);
