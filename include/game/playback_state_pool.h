#ifndef GAME_PLAYBACK_STATE_POOL_H
#define GAME_PLAYBACK_STATE_POOL_H
#include "game/playback_request.h"

/* Matched acquisitions confirm the two pool arrays, 0x68/0x78-byte strides,
 * shared key at 0x28 and claim byte 0x66. UNVERIFIED: original identities and
 * roles, input bounds, full-width key producer contracts, all unaccessed storage
 * and original allocation extents. The extended view records the larger stride. */
typedef struct {
    Recovered_PlaybackState state;
    u8 unk_68[0x10];
} Recovered_ExtendedPlaybackState;

typedef struct {
    Recovered_PlaybackState* states;
    s32 stateCount;
    Recovered_ExtendedPlaybackState* extendedStates;
    s32 extendedStateCount;
    // UNVERIFIED: constructor scratch accesses are not yet source-confirmed.
    s32 scratchBytes;
    void* scratch;
    s32 unk_18;
} Recovered_PlaybackStatePool;

/* Native constructor inputs have a 24-byte stride. Selector 5 uses
 * (dataSize / 19) * 64 as its scratch requirement. UNVERIFIED: original field
 * meanings, format identities, input size units and unused byte 0x17. */
typedef struct {
    u64 key;
    u32 unk_08;
    s32 unk_0C;
    s32 dataSize;
    s8 unk_14, unk_15;
    u8 unk_16, unk_17;
} Recovered_PlaybackStateDefinition;

typedef char PlaybackStateStride[sizeof(Recovered_PlaybackState) == 0x68 ? 1 : -1];
typedef char ExtendedPlaybackStateStride[sizeof(Recovered_ExtendedPlaybackState) == 0x78 ? 1 : -1];
typedef char PlaybackStateKeyOffset[(u32) & ((Recovered_PlaybackState*)0)->poolKey == 0x28 ? 1 : -1];
typedef char PlaybackStateClaimedOffset[(u32) & ((Recovered_PlaybackState*)0)->claimed == 0x66 ? 1 : -1];
typedef char PlaybackDefinitionStride[sizeof(Recovered_PlaybackStateDefinition) == 0x18 ? 1 : -1];
typedef char PlaybackScratchOffset[(u32) & ((Recovered_PlaybackStatePool*)0)->scratch == 0x14 ? 1 : -1];
typedef char PlaybackBuffersCountOffset[(u32) & ((Recovered_PlaybackState*)0)->bufferCount == 0x10 ? 1 : -1];
typedef char ExtendedStateCountOffset[(u32) & ((Recovered_PlaybackStatePool*)0)->extendedStateCount == 0xC ? 1 : -1];

Recovered_PlaybackState* PlaybackStatePool_Acquire(Recovered_PlaybackStatePool* self, u64 key);
Recovered_PlaybackState* PlaybackStatePool_AcquireExtended(Recovered_PlaybackStatePool* self, u64 key);
void PlaybackStatePool_Release(Recovered_PlaybackStatePool* self, Recovered_PlaybackState* state);
void PlaybackStatePool_ReleaseExtended(Recovered_PlaybackStatePool* self, Recovered_PlaybackState* state);
void PlaybackState_SetBuffers(Recovered_PlaybackState* self, Recovered_StreamBuffer** buffers, s32 count);
void PlaybackStatePool_Initialize(Recovered_PlaybackStatePool* self, const Recovered_PlaybackStateDefinition* states,
                                  s32 count, const Recovered_PlaybackStateDefinition* extendedStates,
                                  s32 extendedCount);
#endif
