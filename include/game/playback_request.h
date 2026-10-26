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

/* Partial request interface recovered from native controller call sites.
 * UNVERIFIED: original identities, unused slots, full extents and the producer
 * contract for prepare's full-width tag; the current producer draft uses only
 * its low word. Signed this adjustments are part of each native method record. */
typedef struct {
    s16 thisAdjustment;
    u16 unk_02;
    void* (*function)(void* self);
} Recovered_PlaybackInitializeMethod;
typedef struct {
    s16 thisAdjustment;
    u16 unk_02;
    s32 (*function)(void* self, const u32* values, s32 count, u64 tag);
} Recovered_PlaybackPrepareMethod;
typedef struct {
    s16 thisAdjustment;
    u16 unk_02;
    s32 (*function)(void* self);
} Recovered_PlaybackCompletionMethod;
typedef struct {
    u8 unk_00[8];
    Recovered_PlaybackInitializeMethod initialize;
    Recovered_PlaybackPrepareMethod prepare;
    u8 unk_18[8];
    Recovered_PlaybackCompletionMethod pollComplete;
} Recovered_PlaybackRequestVtable;

typedef struct {
    f32 scale;
    s32 state;
    u64 key; // UNVERIFIED: load request remains a draft.
    Recovered_PlaybackState* playback;
    u32 values[2];
    s32 valueCount;
    void* buffers[2]; // UNVERIFIED: pool operations remain drafts.
    s32 variant;      // UNVERIFIED: load request remains a draft.
    const Recovered_PlaybackRequestVtable* vtable; // UNVERIFIED: controller consumers are pending.
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

typedef char PlaybackRequestVtableOffset[(u32)&((Recovered_PlaybackRequest*)0)->vtable == 0x2C ? 1 : -1];
typedef char PlaybackPrepareOffset[(u32)&((Recovered_PlaybackRequestVtable*)0)->prepare == 0x10 ? 1 : -1];
typedef char PlaybackCompletionOffset[(u32)&((Recovered_PlaybackRequestVtable*)0)->pollComplete == 0x20 ? 1 : -1];
typedef char PlaybackKeyWidth[sizeof(((Recovered_PlaybackRequest*)0)->key) == 8 ? 1 : -1];
typedef char PlaybackKeyOffset[(u32) & ((Recovered_PlaybackRequest*)0)->key == 8 ? 1 : -1];
typedef char PlaybackBuffersOffset[(u32) & ((Recovered_PlaybackRequest*)0)->buffers == 0x20 ? 1 : -1];
typedef char PlaybackVariantOffset[(u32) & ((Recovered_PlaybackRequest*)0)->variant == 0x28 ? 1 : -1];

void* PlaybackRequest_Reset(Recovered_PlaybackRequest* self);
void PlaybackRequest_Update(Recovered_PlaybackRequest* self, Recovered_PlaybackParameters* parameters);
void PlaybackRequest_Begin(Recovered_PlaybackRequest* self, Recovered_PlaybackParameters* parameters);
#endif
