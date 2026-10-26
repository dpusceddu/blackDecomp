#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/ai/priority_queue.h"

extern s32 func_00187018();

extern s32 func_00187C68(Recovered_PriorityQueue*);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_00186E68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_00186F40);

void func_00186FF0(s32 *arg0) {
    if (*arg0 < 0x14) {
        func_00187018();
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_00187018);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_001870C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_00187198);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_001871E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_00187498);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_00187918);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_00187960);

void func_00187B10(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x4B0) = 0;
}

s32 func_00187B18(Recovered_PriorityQueue* self, void* object, s32 tag) {
    s32 i;
    for (i = 0; i < self->count; ++i) {
        if (self->entries[i].object == object) {
            return 0;
        }
    }
    self->entries[self->count].object = object;
    self->entries[self->count].used = 0;
    self->entries[self->count].score = self->table->score((u8*)self + self->table->adjustment, object);
    self->entries[self->count].tag = tag;
    ++self->count;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_00187BF8);

void* func_00187C00(Recovered_PriorityQueue* self, u8* tag) {
    s32 index = (s8)func_00187C68(self);
    if (index < 0) {
        return NULL;
    }
    self->entries[index].used = 1;
    *tag = self->entries[index].tag;
    return self->entries[index].object;
}

s32 func_00187C68(Recovered_PriorityQueue* self) {
    s32 selected = -1;
    f32 best = -1.0f;
    s32 i;
    for (i = 0; i < self->count; ++i) {
        Recovered_PriorityEntry* entry = &self->entries[i];
        if (entry->used) {
            continue;
        }
        if (entry->tag) {
            continue;
        }
        if (best < entry->score) {
            best = entry->score;
            selected = i;
        }
    }
    // Untagged entries take priority; tagged entries are the fallback.
    if (selected != -1) {
        return selected;
    }
    for (i = 0; i < self->count; ++i) {
        if (!self->entries[i].used && best < self->entries[i].score) {
            best = self->entries[i].score;
            selected = i;
        }
    }
    return selected;
}
