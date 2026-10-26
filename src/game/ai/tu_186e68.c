#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/ai/priority_queue.h"
#include "game/ai/movement_candidates.h"
#include "game/timed_flag_queue.h"
#include "game/actor_slots.h"
#include "ps2/vu0_lowering.h"

extern s32 func_001809F0(void*);
extern Recovered_MovementCandidate* func_00180ED8(void*);
extern Recovered_AIManager* D_0040F4D4;
extern s32 func_00177238(Recovered_TimedFlagQueue*, Recovered_TimedFlagItem*, u32);

extern void func_00187018(Recovered_MovementCandidateList*, Recovered_MovementCandidate*, u32, s128, s32);

extern s32 func_00187198(void*, Recovered_MovementCandidate*, Recovered_MovementCandidate*);
extern s32 func_00187B18(Recovered_PriorityQueue*, void*, s32);

extern s32 func_00187C68(Recovered_PriorityQueue*);

extern s128 func_0018D5D0(void*);
extern void* func_0017B6F8(void*, s128);
extern void* func_00181EE8(void*);
extern void func_00187918(Recovered_MovementCandidateList*, u32, s128);
extern void func_001871E8(Recovered_MovementCandidateList*, s128, Recovered_ActorSlot*, s128*, u8*);
extern void func_00187498(Recovered_MovementCandidateList*, void*, u32, s128, s128, u8);

void func_00186E68(Recovered_MovementCandidateList* self, Recovered_ActorSlot* target) {
    s128 point = func_0018D5D0((u8*)self->owner + 0xD10);
    void* selection = func_0017B6F8((u8*)D_0040F4D4 + 0x1290, point);
    u32 flags = ActorSlot_Mask(target);
    self->count = 0;
    self->unk_68[0] = M2C_FIELD(func_00181EE8((u8*)self->owner + 0xEC0), u8*, 0x78);
    func_00187918(self, flags, point);
    if (selection != NULL) {
        s128 offset;
        u8 tag;
        func_001871E8(self, point, target, &offset, &tag);
        func_00187498(self, selection, flags, point, offset, tag);
    }
}

extern void* D_0040F4D0;
extern s32 func_0018DDD8(void*);
extern s32 func_0018D2F8(void*, const s128*);

s32 func_00186F40(Recovered_MovementCandidateList* self, const s128* point) {
    s128 captured = *point;
    if (!func_0018DDD8((u8*)self->owner + 0xC94)) {
        if (!self->unk_68[0]) {
            BkVuVector a = captured;
            BkVuVector one = BkVuOneX();
            BkVuVector b = M2C_FIELD(D_0040F4D0, s128*, 0xD0);
            BkVuVector delta = BkVuSubXYZ(a, b);
            f32 distanceSquared = __ee_vu_read_x(BkVuSumXYZ(BkVuMulXYZ(delta, delta), one));
            if (distanceSquared < 25.0f) {
                return 1;
            }
        }
    }
    return func_0018D2F8((u8*)self->owner + 0xD10, point) == 0;
}

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

s32 func_00187198(void* self, Recovered_MovementCandidate* first, Recovered_MovementCandidate* second) {
    BkVuVector a = first->point;
    BkVuVector one = BkVuOneX();
    BkVuVector b = second->point;
    BkVuVector delta = BkVuSubXYZ(b, a);
    f32 distanceSquared = __ee_vu_read_x(BkVuSumXYZ(BkVuMulXYZ(delta, delta), one));
    return distanceSquared <= 0.09f;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_001871E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_00187498);
extern void func_0018D8A8(void*, void*, u32, s128);

void func_00187918(Recovered_MovementCandidateList* self, u32 flags, s128 point) {
    void* movement = (u8*)self->owner + 0xD10;
    if (M2C_FIELD(movement, s32*, 0x20) == 5) {
        func_0018D8A8(movement, self, flags, point);
    }
}

#ifdef NON_MATCHING
// Unmatched: tiny-distance constant lifetime and vector spill ordering differ.
extern const s128* func_00185FE8(void*);
extern const s128* func_00185F10(void*);
extern const s128* func_001893A0(void*);

s32 func_00187960(Recovered_MovementCandidateList* self, s32 alternate) {
    s128 origin = M2C_FIELD(M2C_FIELD(self->owner, void**, 0x7C), s128*, 0xA0);
    const s128* destination;
    BkVuVector one;
    BkVuVector delta, sum, direction;
    BkVuVector other, otherSum, otherDirection;
    f32 distanceSquared, alignment;
    if (alternate) destination = func_00185FE8(self);
    else destination = func_00185F10(self);
    delta = BkVuSubXYZ(*destination, origin);
    one = BkVuOneX();
    sum = BkVuSumXYZ(BkVuMulXYZ(delta, delta), one);
    distanceSquared = __ee_vu_read_x(sum);
    if ((u8)(distanceSquared < 2.3283064365386962890625e-10f)) return 2;
    sum = BkVuSumXYZ(BkVuMulXYZ(delta, delta), one);
    direction = BkVuNormalizeXYZ(delta, sum);
    other = BkVuSubXYZ(*func_001893A0((u8*)self->owner + 0x150), origin);
    otherSum = BkVuSumXYZ(BkVuMulXYZ(other, other), one);
    distanceSquared = __ee_vu_read_x(otherSum);
    if ((u8)(distanceSquared < 2.3283064365386962890625e-10f)) return 2;
    otherSum = BkVuSumXYZ(BkVuMulXYZ(other, other), one);
    otherDirection = BkVuNormalizeXYZ(other, otherSum);
    alignment = __ee_vu_read_x(BkVuSumXYZ(BkVuMulXYZ(direction, otherDirection), BkVuOneX()));
    if (0.7f < alignment) return 0;
    if (alignment < -0.7f) return 1;
    return 2;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_186e68", func_00187960);
#endif

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
