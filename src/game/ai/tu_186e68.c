#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/ai/priority_queue.h"
#include "game/ai/movement_candidates.h"
#include "game/timed_flag_queue.h"

extern s32 func_001809F0(void*);
extern Recovered_MovementCandidate* func_00180ED8(void*);
extern void* D_0040F4D4;
extern s32 func_00177238(Recovered_TimedFlagQueue*, Recovered_TimedFlagItem*, u32);

extern void func_00187018(Recovered_MovementCandidateList*, Recovered_MovementCandidate*, u32, s128, s32);

extern s32 func_00187198(void*, Recovered_MovementCandidate*, Recovered_MovementCandidate*);
extern s32 func_00187B18(Recovered_PriorityQueue*, void*, s32);

extern s32 func_00187C68(Recovered_PriorityQueue*);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_00186E68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_00186F40);

void func_00186FF0(Recovered_MovementCandidateList* self, Recovered_MovementCandidate* candidate,
                   u32 flags, s128 point, s32 tag) {
    if (self->count < 20) {
        func_00187018(self, candidate, flags, point, tag);
    }
}

void func_00187018(Recovered_MovementCandidateList* self, Recovered_MovementCandidate* candidate, u32 flags, s128 point, s32 tag) {
    if (candidate->unk_24 == 0) {
        if (candidate->unk_40 == func_001809F0((u8*)self->owner + 0xB30)) {
            Recovered_MovementCandidate* replacement = func_00180ED8((u8*)self->owner + 0xB30);
            if (replacement != NULL) {
                candidate = replacement;
            }
        }
    }
    func_00177238((Recovered_TimedFlagQueue*)((u8*)D_0040F4D4 + 0x78),
                  (Recovered_TimedFlagItem*)candidate, flags);
    self->tags[self->count] = tag;
    {
        s32 index = self->count;
        self->candidates[index] = candidate;
        self->count = index + 1;
    }
}

s32 func_001870C8(void* self, Recovered_MovementCandidate* object, Recovered_PriorityQueue* queue, s32 tag) {
    s32 inserted = 0;
    s32 hasEquivalent = 0;
    Recovered_MovementCandidate* node;
    for (node = object->next; node != NULL; node = node->next) {
        inserted |= func_00187B18(queue, node, tag) != 0;
        hasEquivalent |= func_00187198(self, object, node) != 0;
    }
    if (!hasEquivalent) {
        inserted |= func_00187B18(queue, object, tag) != 0;
    }
    return inserted;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_00187198);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_001871E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_00187498);
extern void func_0018D8A8(void*, void*, void*, s128);

void func_00187918(Recovered_MovementCandidateList* self, void* target, s128 point) {
    void* movement = (u8*)self->owner + 0xD10;
    if (M2C_FIELD(movement, s32*, 0x20) == 5) {
        func_0018D8A8(movement, self, target, point);
    }
}

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
