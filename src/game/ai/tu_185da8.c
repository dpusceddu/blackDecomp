#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/vu0_lowering.h"
#include "game/actor_slots.h"
#include "game/ai/movement_candidates.h"

extern s32 func_00176F00();
extern void func_00186E68(Recovered_MovementCandidateList*, Recovered_ActorSlot*);
extern s32 func_00186988(Recovered_MovementCandidateList*, Recovered_ActorSlot*);
extern s32 func_00185FF0(Recovered_MovementCandidateList*, Recovered_ActorSlot*, s32);
void func_00186218(Recovered_MovementCandidateList*, Recovered_ActorSlot*, s32);
extern void* func_00177A98(Recovered_MovementCandidate*);
extern void func_00177AD0(Recovered_MovementCandidate*);
extern s32 func_00177AA0(Recovered_MovementCandidate*, void*);
extern s32 func_00177B80(Recovered_MovementCandidate*, s32);
extern f32 func_00185350(void*, s32);
extern const s128* func_00178D30(Recovered_ActorSlot*);
extern s32 func_00182270(void*, s128, f32);
void func_00186308(Recovered_MovementCandidateList*, s32);

void func_00185DA8(Recovered_MovementCandidateList* self) {
    Recovered_ActorSlot* target =
        ActorRecords_CurrentOrFallback((Recovered_ActorRecords*)((u8*)self->owner + 0x150));
    if (func_00176F00((u8*)self->owner + 0x1FCC) & 0xFF) {
        func_00186E68(self, target);
    }
    func_00186988(self, target);
    func_00185FF0(self, target, self->channels[0].disabled ^ 1);
    func_00186218(self, target, self->channels[1].disabled ^ 1);
}

#ifdef NON_MATCHING
// Unmatched: selected-pointer load and branch delay-slot scheduling differ.
void func_00185E38(Recovered_MovementCandidateList* self) {
    s32 i;
    for (i = 0; i < 20; ++i) {
        self->candidates[i] = 0;
        self->tags[i] = 0;
    }
    self->count = 0;
    {
        u8* reached = &self->channels[0].reached;
        Recovered_MovementCandidate** proposed = &self->channels[0].proposed;
        Recovered_MovementCandidate** selected = &self->channels[0].selected;
        s32 end = (s32)selected + 2 * sizeof(Recovered_MovementCandidateChannel);
        do {
            if (*selected) {
                if (func_00177A98(*selected) == self->owner) func_00177AD0(*selected);
            }
            *proposed = 0;
            *selected = 0;
            proposed = (Recovered_MovementCandidate**)((u8*)proposed + sizeof(Recovered_MovementCandidateChannel));
            *reached = 0;
            selected = (Recovered_MovementCandidate**)((u8*)selected + sizeof(Recovered_MovementCandidateChannel));
            reached += sizeof(Recovered_MovementCandidateChannel);
        } while ((s32)selected < end);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_185da8", func_00185E38);
#endif

s32 func_00185F00(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x70) != 0;
}

s32 func_00185F10(s32 arg0) {
    return arg0 + 0x90;
}

s32 func_00185F18(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x7C) != 0;
}

s32 func_00185F28(Recovered_MovementCandidateList* self) {
    if (self->channels[1].selected) {
        Recovered_ActorSlot* target = ActorRecords_CurrentOrFallback((Recovered_ActorRecords*)((u8*)self->owner + 0x150));
        if (!func_00177B80(self->channels[1].selected, target->index)) {
            f32 radius = func_00185350((u8*)self->owner + 0x6F0, 0);
            f32 radiusSquared = radius * radius;
            Recovered_MovementCandidate* candidate = self->channels[1].selected;
            const s128* point = func_00178D30(
                ActorRecords_CurrentOrFallback((Recovered_ActorRecords*)((u8*)self->owner + 0x150)));
            BkVuVector b = *point;
            BkVuVector one = BkVuOneX();
            BkVuVector a = candidate->point;
            BkVuVector delta = BkVuSubXYZ(a, b);
            f32 squared = __ee_vu_read_x(BkVuSumXYZ(BkVuMulXYZ(delta, delta), one));
            return !(radiusSquared < squared);
        }
    }
    return 0;
}

s32 func_00185FE8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x7C);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_185da8", func_00185FF0);
void func_00186218(Recovered_MovementCandidateList* self, Recovered_ActorSlot* target, s32 enabled) {
    Recovered_MovementCandidate* selected = self->channels[1].selected;
    if (selected && !selected->methods->test((u8*)selected + selected->methods->adjustment)) {
        func_00186308(self, 1);
    }
    if (enabled) {
        if (self->channels[1].available && self->channels[1].proposed) {
            if (self->channels[1].proposed != self->channels[1].selected &&
                func_00177AA0(self->channels[1].proposed, self->owner)) {
                if (self->channels[1].selected) func_00186308(self, 1);
                self->channels[1].selected = self->channels[1].proposed;
            }
        } else if (self->channels[1].selected) {
            func_00186308(self, 1);
        }
    }
    if (self->channels[1].selected) {
        self->channels[1].reached = func_00182270((u8*)self->owner + 0x810,
                                               self->channels[1].selected->point, 0.25f);
    } else {
        self->channels[1].reached = 0;
    }
}

void func_00186308(Recovered_MovementCandidateList* self, s32 index) {
    /* Both channels may select the same candidate; clear its owner only when
     * the other channel no longer retains it. The native index domain is 0/1. */
    s32 base = (s32)&self->channels[0].selected;
    s32 offset = index * sizeof(Recovered_MovementCandidateChannel);
    u8 otherIndex = (index ^ 1) != 0;
    s32 otherOffset = otherIndex * sizeof(Recovered_MovementCandidateChannel);
    Recovered_MovementCandidate** selected = (Recovered_MovementCandidate**)(base + offset);
    Recovered_MovementCandidate** other = (Recovered_MovementCandidate**)(base + otherOffset);
    Recovered_MovementCandidate* candidate = *selected;
    *selected = 0;
    if (*other != candidate) func_00177AD0(candidate);
}
