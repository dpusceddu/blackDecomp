#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00181C20();
extern s32 func_00176F00(s32);
extern void func_00181AD0(void *arg0, s32 arg1);
extern s32 func_00181D20();
extern void func_00181DA0(void *arg0);

void func_00181418(void *arg0) {
    func_00181C20(arg0);
    if (func_00176F00(M2C_FIELD(arg0, s32 *, 0x714) + 0x1FCC) & 0xFF) {
        func_00181AD0(arg0, 7);
    }
    func_00181D20(arg0);
    func_00181DA0(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1804f8_181418", func_00181470);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1804f8_181418", func_001814E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1804f8_181418", func_00181560);
