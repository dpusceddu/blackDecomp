#include "include_asm.h"
#include "ps2/prelude.h"

extern void * func_001AFD80();
extern s32 func_001484C8();

s32 func_00145FB0(void *arg0) {
    void *temp_2;

    temp_2 = func_001AFD80(M2C_FIELD(arg0, s32 *, 0x1A0) + (func_001484C8() * 0xC), M2C_FIELD(arg0, s32 *, 0x118));
    if (temp_2 == NULL) {
        return 0;
    }
    return ((u16) M2C_FIELD(temp_2, u16 *, 0x5A) >> 0xF) ^ 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_145fb0", func_00146000);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_145fb0", func_001463D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_145fb0", func_00146578);
