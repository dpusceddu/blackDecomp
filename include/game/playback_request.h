#ifndef GAME_PLAYBACK_REQUEST_H
#define GAME_PLAYBACK_REQUEST_H
#include "ps2/prelude.h"

/* Partial native views. The original class identity, complete allocations and
 * meanings of the numeric lifecycle states are not yet established. */
typedef struct {
    u8 unk_00[0x34];
    f32 unk_34;
    u8 unk_38[4];
    f32 unk_3C;
} Recovered_PlaybackState;

typedef struct {
    f32 scale;
    s32 state;
    u64 key; // UNVERIFIED: load request remains a draft.
    Recovered_PlaybackState* playback;
    u32 values[2];
    s32 valueCount;
    void* buffers[2]; // UNVERIFIED: pool operations remain drafts.
    s32 variant;      // UNVERIFIED: load request remains a draft.
} Recovered_PlaybackRequest;

typedef struct {
    u8 unk_00[0x54];
    f32 scale;
    u32 unk_58;
    u8 unk_5C[0x48];
    u32 flags;
} Recovered_PlaybackParameters;

/* UNVERIFIED: accessed only by the pool-operation drafts. */
typedef struct {
    u8 unk_00[0x4BD4];
    void* buffers;
    void* unk_4BD8;
    void* states;
} Recovered_PlaybackPools;

typedef struct {
    u8 unk_00[0x8000];
    Recovered_PlaybackPools playbackPools;
} Recovered_PlaybackServices;

typedef char PlaybackKeyWidth[sizeof(((Recovered_PlaybackRequest*)0)->key) == 8 ? 1 : -1];
typedef char PlaybackKeyOffset[(u32) & ((Recovered_PlaybackRequest*)0)->key == 8 ? 1 : -1];
typedef char PlaybackBuffersOffset[(u32) & ((Recovered_PlaybackRequest*)0)->buffers == 0x20 ? 1 : -1];
typedef char PlaybackVariantOffset[(u32) & ((Recovered_PlaybackRequest*)0)->variant == 0x28 ? 1 : -1];

void* PlaybackRequest_Reset(Recovered_PlaybackRequest* self);
void PlaybackRequest_Update(Recovered_PlaybackRequest* self, Recovered_PlaybackParameters* parameters);
void PlaybackRequest_Begin(Recovered_PlaybackRequest* self, Recovered_PlaybackParameters* parameters);
#endif
