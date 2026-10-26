#ifndef GAME_TRANSITION_H
#define GAME_TRANSITION_H
#include "ps2/prelude.h"

/* Accessed native prefixes. The full state allocation and original class names
 * remain unknown. The controller stores current and pending state pointers. */
typedef struct {
    s16 adjustment;
    u16 unk_02;
    s32 (*call)(void*);
} Recovered_TransitionVirtual;

typedef struct {
    u8 unk_00[8];
    Recovered_TransitionVirtual* methods;
} Recovered_TransitionState;

/* UNVERIFIED: only the draft entry lookup accesses this record. */
typedef struct {
    u8 unk_00[0x58];
    u8 id;
    u8 unk_59[7];
} Recovered_TransitionEntry;

typedef struct {
    u8 unk_00[0x10];
    u8 id;
    u8 unk_11[3];
    Recovered_TransitionEntry* sets[3]; // UNVERIFIED: entry lookup remains a draft.
    u8 counts[3];                       // UNVERIFIED: entry lookup remains a draft.
    u8 unk_23;
} Recovered_TransitionGroup;

typedef struct {
    u8 count;
    u8 unk_01[3];
    Recovered_TransitionGroup* groups;
} Recovered_TransitionCatalog;

typedef struct {
    u8 unk_00[0x20F78];
    Recovered_TransitionState defaultState; // UNVERIFIED: transition scheduling remains a draft.
    u8 unk_20F84[0xE8];
    Recovered_TransitionCatalog* catalog;
    Recovered_TransitionState* current;
    Recovered_TransitionState* pending; // UNVERIFIED: pending-state polling remains a draft.
    u8 unk_21078[0xC];
    s32 phase;
    u32 scratch[6];  // UNVERIFIED: transition scheduling remains a draft.
    u8 timing[0x24]; // UNVERIFIED: transition scheduling remains a draft.
    s32 cycle;       // UNVERIFIED: transition scheduling remains a draft.
    u8 unk_210C8;    // UNVERIFIED: transition scheduling remains a draft.
    u8 unk_210C9[2];
    u8 unk_210CB; // UNVERIFIED: transition scheduling remains a draft.
    u8 unk_210CC;
} Recovered_TransitionContext;

/* UNVERIFIED: service fields are accessed only by scheduling/polling drafts. */
typedef struct {
    u8 active;
    u8 unk_01[0x3947];
    f32 amount;
    u8 enabled;
} Recovered_TransitionServices;

typedef char TransitionGroupStride[sizeof(Recovered_TransitionGroup) == 0x24 ? 1 : -1];
typedef char TransitionEntryStride[sizeof(Recovered_TransitionEntry) == 0x60 ? 1 : -1];
typedef char TransitionCatalogOffset[(u32) & ((Recovered_TransitionContext*)0)->catalog == 0x2106C ? 1 : -1];
typedef char TransitionTimingOffset[(u32) & ((Recovered_TransitionContext*)0)->timing == 0x210A0 ? 1 : -1];
typedef char TransitionCycleOffset[(u32) & ((Recovered_TransitionContext*)0)->cycle == 0x210C4 ? 1 : -1];

void Transition_ClearFrame(Recovered_TransitionContext* self);
/* Identical retail body; the distinction between these entry points is unknown. */
void Transition_ClearFrameCopy(Recovered_TransitionContext* self);
Recovered_TransitionGroup* Transition_FindGroup(Recovered_TransitionContext* self, s32 id);
s32 Transition_PollCurrent(Recovered_TransitionContext* self);

#endif
