#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
#include "game/actor/entry_counts.h"

s32 func_00149120(s32 *arg0, s32 arg1) {
    s32 var_3;
    s32 var_5;

    var_5 = arg1;
    var_3 = 0;
    if (var_5 != -1) {
        do {
            var_5 = M2C_FIELD(((var_5 * 4) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x118), s32 *, 0x58)), s32 *, 0);
            var_3 += 1;
        } while (var_5 != -1);
    }
    return var_3;
}

#ifdef NON_MATCHING
// Unmatched: eight counter/accumulator register operands differ.
s32 func_00149178(Recovered_ActorCountView *self) {
    s32 remaining = self->entryCount;
    s32 total = 0;
    if (remaining) {
        Recovered_ActorCountSourceEntry *entry = self->source->entries;
        do {
            s32 count = entry->count;
            if (!count)
                total += 1;
            else
                total += count;
            --remaining;
            ++entry;
        } while (remaining);
    }
    return total;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_149120", func_00149178);
#endif

s32 func_001491B8(Recovered_ActorCountView *self, s32 index, s32 *count) {
    s32 total = 0;
    if (index > 0) {
        s32 remaining = index;
        u8 *entry = &self->entries->count;
        do {
            total += *entry;
            --remaining;
            entry += 0xC;
        } while (remaining);
    }
    if (count) *count = self->entries[index].count;
    return total;
}

s32 func_00149210(Recovered_ActorCountView* self, s32 index) {
    s32 total = 0;
    s32 i;
    for (i = 0; i < self->entryCount; ++i) {
        total += self->entries[i].count;
        if (index < total) return i;
    }
    return -1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_149120", func_00149260);
