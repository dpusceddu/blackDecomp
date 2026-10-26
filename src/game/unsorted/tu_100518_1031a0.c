#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/effects/render_state.h"
#include "game/transition.h"

#include "ps2/recovered_types.h"
extern s32 func_00107E28(s32);
extern s32 func_0012A0D8(s32);
extern s32 * D_0040F4D0;

s32 func_001031A0(s32 arg0) {
    s32 var_16;
    s32 var_17;

    var_16 = arg0 + 0x21060;
    var_17 = 0;
    do {
        var_17 -= 1;
        func_00107E28(var_16);
        var_16 += 0xC;
    } while (var_17 >= 0);
    return func_0012A0D8((s32) D_0040F4D0);
}

extern BkActorRenderPS2* D_0040F4C0;
extern Recovered_TransitionContext* D_0040F0E0;
extern void* D_0040F0E8;
extern Recovered_TransitionServices* D_0040F544;
extern u8 D_003F2520[];
extern void* memset(void*, s32, u32);
extern void* func_002A9108(void*, void*, s32);
extern void func_00274540(void);
extern void func_00107A00(void*);
extern void func_001C4FB0(BkActorRenderPS2*, s32);
extern void func_0020B170(Recovered_TransitionServices*);
extern void func_001C50E0(BkActorRenderPS2*);
extern void func_00271480(void);
extern void func_0020B0C0(Recovered_TransitionServices*);
extern void func_00216F08(void*);
extern void func_00217010(void*);
extern void func_0020B678(Recovered_TransitionServices*, void*, s32);
extern void func_0020B988(Recovered_TransitionServices*, s32);
extern void func_00103800(Recovered_TransitionContext*, s8);

static inline void TransitionClearFrame(Recovered_TransitionContext* self) {
    BkRenderBufferPS2* buffer = &D_0040F4C0->buffers[0];
    u32 clearValue;
    memset(&clearValue, 0, sizeof(clearValue));
    func_002A9108(buffer->geometry, &clearValue, 3);
    func_00274540();
    if (self->unk_210CC) func_00107A00(D_0040F0E8);
    func_001C4FB0(D_0040F4C0, 0);
    func_0020B170(D_0040F544);
    func_001C50E0(D_0040F4C0);
    func_00271480();
}

void Transition_ClearFrame(Recovered_TransitionContext* self) { TransitionClearFrame(self); }

void Transition_ClearFrameCopy(Recovered_TransitionContext* self) { TransitionClearFrame(self); }

Recovered_TransitionGroup* Transition_FindGroup(Recovered_TransitionContext* self, s32 id) {
    Recovered_TransitionCatalog* catalog = self->catalog;
    s32 i;
    for (i = 0; i < catalog->count; i++) {
        if (catalog->groups[i].id == id) return &catalog->groups[i];
    }
    return NULL;
}

#ifdef NON_MATCHING
// Unmatched: group-scan conditional move replaces the native likely branch.
Recovered_TransitionEntry* func_001033A0(Recovered_TransitionContext* self, u8 groupId, u8 entryId) {
    Recovered_TransitionCatalog* catalog = self->catalog;
    Recovered_TransitionGroup* selected = NULL;
    s32 count = catalog->count;
    u8 i;
    if (count != 0) {
        Recovered_TransitionGroup* group = catalog->groups;
        s32 remaining = count;
        do {
            if (group->id == groupId) selected = group;
            remaining--;
            group++;
        } while (remaining != 0);
    }
    /* As in the native path, the requested group must exist. */
    for (i = 0; i < selected->counts[0]; i++) {
        if (selected->sets[0][i].id == entryId) return &selected->sets[0][i];
    }
    for (i = 0; i < selected->counts[1]; i++) {
        if (selected->sets[1][i].id == entryId) return &selected->sets[1][i];
    }
    for (i = 0; i < selected->counts[2]; i++) {
        if (selected->sets[2][i].id == entryId) return &selected->sets[2][i];
    }
    return NULL;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518_1031a0", func_001033A0);
#endif

#ifdef NON_MATCHING
// Unmatched: cycle reload registers and final state-store scheduling differ.
void func_001034B0(Recovered_TransitionContext* self, Recovered_TransitionState* next) {
    func_0020B0C0(D_0040F544);
    func_00216F08(self->timing);
    switch (self->cycle) {
        case 0:
            func_0020B678(D_0040F544, D_003F2520, 5);
            self->cycle++;
            break;
        case 1:
            func_0020B678(D_0040F544, D_003F2520, 5);
            self->cycle++;
            break;
        default:
            func_0020B678(D_0040F544, D_003F2520, 5);
            self->cycle = 0;
            break;
    }
    if (next == &D_0040F0E0->defaultState) func_00217010(self->timing);
    self->pending = next;
    self->unk_210CB = 1;
    self->phase = 2;
    self->unk_210C8 = 0;
    {
        Recovered_TransitionServices* services = D_0040F544;
        services->enabled = 1;
        services->amount = 1.0f;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518_1031a0", func_001034B0);
#endif

#ifdef NON_MATCHING
// Unmatched: cycle reload registers and state/service store scheduling differ.
void func_001035D0(Recovered_TransitionContext* self) {
    self->pending = self->current;
    func_0020B0C0(D_0040F544);
    func_00216F08(self->timing);
    switch (self->cycle) {
        case 0:
            func_0020B678(D_0040F544, D_003F2520, 5);
            self->cycle++;
            break;
        case 1:
            func_0020B678(D_0040F544, D_003F2520, 5);
            self->cycle++;
            break;
        default:
            func_0020B678(D_0040F544, D_003F2520, 5);
            self->cycle = 0;
            break;
    }
    if (self->current == &D_0040F0E0->defaultState) func_00217010(self->timing);
    self->unk_210C8 = 0;
    self->unk_210CB = 1;
    self->scratch[0] = 0;
    self->scratch[1] = 0;
    self->scratch[4] = 0;
    self->scratch[5] = 0;
    {
        Recovered_TransitionServices* services = D_0040F544;
        services->amount = 1.0f;
        services->enabled = 1;
        self->phase = 1;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518_1031a0", func_001035D0);
#endif

#ifdef NON_MATCHING
// Unmatched: service pointer reload is hoisted across current/pending stores.
s32 func_001036F0(Recovered_TransitionContext* self) {
    Recovered_TransitionState* pending = self->pending;
    Recovered_TransitionVirtual* methods = pending->methods;
    if (!methods[1].call((s8*)pending + methods[1].adjustment)) return 0;
    func_0020B988(D_0040F544, 5);
    func_0020B988(D_0040F544, 6);
    self->current = self->pending;
    self->pending = NULL;
    {
        Recovered_TransitionServices* services = D_0040F544;
        if (services->active && self->current == &self->defaultState) func_00103800(self, 1);
    }
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518_1031a0", func_001036F0);
#endif

s32 Transition_PollCurrent(Recovered_TransitionContext* self) {
    Recovered_TransitionState* current = self->current;
    Recovered_TransitionVirtual* methods = current->methods;
    if (!methods[4].call((s8*)current + methods[4].adjustment)) return 0;
    self->phase = 1;
    return 1;
}
