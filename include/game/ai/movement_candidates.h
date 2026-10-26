#ifndef GAME_AI_MOVEMENT_CANDIDATES_H
#define GAME_AI_MOVEMENT_CANDIDATES_H

#include "ps2/prelude.h"

/* Partial PS2 views. The candidate accepts timed flags; the meanings of its
 * +0x24 and +0x40 fields remain unknown.
 * UNVERIFIED: unaccessed byte spans and total object extents are not confirmed. */
typedef struct Recovered_MovementCandidate {
    u8 unk_00[0x24];
    s32 unk_24;
    u8 unk_28[4];
    struct Recovered_MovementCandidate* next;
    u8 unk_30[0x10];
    s32 unk_40;
} Recovered_MovementCandidate;

typedef struct {
    s32 count;
    Recovered_MovementCandidate* candidates[20];
    u8 tags[20];
    u8 unk_68[0x3C];
    void* owner;
} Recovered_MovementCandidateList;

typedef char MovementCandidateNext[(u32)&((Recovered_MovementCandidate*)0)->next == 0x2C ? 1 : -1];
typedef char MovementCandidateTags[(u32)&((Recovered_MovementCandidateList*)0)->tags == 0x54 ? 1 : -1];
typedef char MovementCandidateOwner[(u32)&((Recovered_MovementCandidateList*)0)->owner == 0xA4 ? 1 : -1];

#endif
