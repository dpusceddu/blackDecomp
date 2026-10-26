#ifndef GAME_AI_MOVEMENT_CANDIDATES_H
#define GAME_AI_MOVEMENT_CANDIDATES_H

#include "ps2/prelude.h"

/* Partial PS2 views. The candidate accepts timed flags; the meanings of its
 * +0x24 and +0x40 fields remain unknown.
 * UNVERIFIED: unaccessed byte spans and total object extents are not confirmed. */
/* The channel-selection update confirms this adjusted native method slot;
 * its broader gameplay contract remains unknown. */
typedef struct {
    u8 unk_00[8];
    s16 adjustment;
    u16 unk_0A;
    s32 (*test)(void*);
} Recovered_MovementCandidateMethods;

typedef struct Recovered_MovementCandidate {
    s128 point;
    u8 unk_10[0x14];
    s32 unk_24;
    void* owner;
    struct Recovered_MovementCandidate* next;
    Recovered_MovementCandidateMethods* methods;
    u8 unk_34[0xC];
    s32 unk_40;
} Recovered_MovementCandidate;

/* A proposed and a selected candidate share one channel. The two channel
 * indices have not yet been assigned gameplay names. Selection and release
 * confirm the accessed pointers and state bytes. */
typedef struct {
    Recovered_MovementCandidate* proposed;
    Recovered_MovementCandidate* selected;
    u8 available;
    u8 reached;
    u8 disabled;
    u8 unk_0B;
} Recovered_MovementCandidateChannel;

typedef struct {
    s32 count;
    Recovered_MovementCandidate* candidates[20];
    u8 tags[20];
    u8 unk_68[4];
    Recovered_MovementCandidateChannel channels[2];
    u8 unk_84[0xC];
    s128 selectedPoint; // UNVERIFIED: captured-point consumers remain drafts.
    u8 selectedFlags[2]; // UNVERIFIED: captured-flag consumers remain drafts.
    u8 unk_A2[2];
    void* owner;
} Recovered_MovementCandidateList;

typedef char MovementCandidateMethods[(u32)&((Recovered_MovementCandidate*)0)->methods == 0x30 ? 1 : -1];
typedef char MovementCandidateNext[(u32)&((Recovered_MovementCandidate*)0)->next == 0x2C ? 1 : -1];
typedef char MovementCandidateTags[(u32)&((Recovered_MovementCandidateList*)0)->tags == 0x54 ? 1 : -1];
typedef char MovementCandidateChannelStride[sizeof(Recovered_MovementCandidateChannel) == 12 ? 1 : -1];
typedef char MovementCandidateChannels[(u32)&((Recovered_MovementCandidateList*)0)->channels == 0x6C ? 1 : -1];
typedef char MovementCandidateSelectedPoint[(u32)&((Recovered_MovementCandidateList*)0)->selectedPoint == 0x90 ? 1 : -1];
typedef char MovementCandidateOwner[(u32)&((Recovered_MovementCandidateList*)0)->owner == 0xA4 ? 1 : -1];

#endif
