#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/actor/entry_counts.h"

extern void * func_001AFD80(void *, s32, s32);

s32 func_00148498(void *arg0, s32 arg1) {
    s32 temp_6;

    temp_6 = arg1 * 0xC;
    return func_001AFD80(M2C_FIELD(arg0, s32 *, 0x1A0) + temp_6, M2C_FIELD(arg0, s32 *, 0x118), temp_6) + 0x90;
}

s32 func_001484C8(Recovered_ActorCountView* self) {
    s32 i;
    for (i = 0; i < self->slotCount; ++i) {
        if (self->indices[i] == -1) return i;
    }
    return -1;
}

void* func_00148508(Recovered_ActorCountView* self, u8 slot) {
    s32 index = self->indices[slot];
    if (index != -1) return &self->matrices[index];
    if (self->unk_1F0) return (u8*)self + 0x140;
    return (u8*)self + 0x70;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_148498", func_00148550);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_148498", func_00148BE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_148498", func_00148D10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_148498", func_00148FF8);
