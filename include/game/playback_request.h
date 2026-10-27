#ifndef GAME_PLAYBACK_REQUEST_H
#define GAME_PLAYBACK_REQUEST_H
#include "ps2/prelude.h"
#include "game/stream_buffer.h"

/* Partial native views. The original class identity, complete allocations and
 * meanings of the numeric lifecycle states are not yet established. */
typedef struct {
    // Buffer slots/count are confirmed by the matched attachment routine.
    Recovered_StreamBuffer* buffers[4];
    s32 bufferCount;
    // Execution offsets are confirmed by matched state consumers; original field meanings remain UNVERIFIED.
    s32 unk_14, unk_18, unk_1C;
    u64 unk_20;
    u64 poolKey; // Confirmed by matched keyed pool acquisitions.
    u32 unk_30;
    f32 unk_34;
    u32 unk_38;
    f32 unk_3C;
    Recovered_StreamRange* unk_40;
    Recovered_StreamBuffer* unk_44;
    s32 unk_48, unk_4C, unk_50, unk_54, unk_58, unk_5C;
    s16 unk_60, unk_62;
    u8 unk_64, unk_65;
    u8 claimed; // Confirmed by matched keyed pool acquisitions.
    u8 unk_67;
} Recovered_PlaybackState;

/* Partial request interface recovered from native controller call sites.
 * UNVERIFIED: original identities, unused slots, full extents and the producer
 * tag semantics. Native controller calls forward all 64 tag bits; signed this
 * adjustments are part of each native method record. */
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
    Recovered_StreamBuffer* buffers[2]; // UNVERIFIED: request pool operations remain drafts.
    Recovered_StreamRange* variant; // UNVERIFIED: request binding remains draft-backed.
    const Recovered_PlaybackRequestVtable* vtable; // Confirmed by matched controller consumers.
} Recovered_PlaybackRequest;

typedef struct {
    u8 unk_00[0x54];
    f32 scale;
    u32 unk_58;
    u8 unk_5C[0x48];
    u32 flags;
    // Native parameter transport copies eleven aligned quadwords.
    u8 unk_A8, unk_A9, unk_AA, unk_AB;
    u32 unk_AC;
} Recovered_PlaybackParameters __attribute__((aligned(16)));
typedef char PlaybackParameterCopyExtent[sizeof(Recovered_PlaybackParameters) == 0xB0 ? 1 : -1];

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
