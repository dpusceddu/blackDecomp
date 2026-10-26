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
// Unmatched: the loop code differs; draft left when the session ended.
s32 func_00149178(Recovered_ActorCountView *self) {
    s32 remaining = self->entryCount;
    s32 total = 0;
    if (remaining) {
        Recovered_ActorCountSourceEntry *entry = self->source->entries;
        do {
            s32 count = entry->count;
            if (count) total += count;
            else total += 1;
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

#ifdef NON_MATCHING
// Unmatched: compiles to 72 bytes instead of 80.
s32 func_00149210(Recovered_ActorCountView *self, s32 index) {
    s32 i;
    s32 total;
    u8 count;

    count = self->entryCount;
    total = 0;
    i = 0;
    if (count) {
        u8 *entry = &self->entries->count;
        do {
            total += *entry;
            if (index < total) return i;
            ++i;
            entry += 0xC;
        } while (i < count);
    }
    return -1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_149120", func_00149210);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_149120", func_00149260);
