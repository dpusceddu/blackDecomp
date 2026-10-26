#ifndef GAME_PLAYBACK_STATE_POOL_H
#define GAME_PLAYBACK_STATE_POOL_H
#include "game/playback_request.h"

/* Partial pool views from the paired native acquisition loops. The first array
 * has a 0x68-byte stride and the second 0x78; both compare the 64-bit key at 0x28
 * and claim byte 0x66. UNVERIFIED until matched consumers: these pool accesses,
 * original identities and roles, input bounds, producer contracts for the full
 * key width, all unaccessed storage and total allocation extents. The extended view records only the observed larger stride. */
typedef struct {
    Recovered_PlaybackState state;
    u8 unk_68[0x10];
} Recovered_ExtendedPlaybackState;

typedef struct {
    Recovered_PlaybackState* states;
    s32 stateCount;
    Recovered_ExtendedPlaybackState* extendedStates;
    s32 extendedStateCount;
} Recovered_PlaybackStatePool;

typedef char PlaybackStateStride[sizeof(Recovered_PlaybackState) == 0x68 ? 1 : -1];
typedef char ExtendedPlaybackStateStride[sizeof(Recovered_ExtendedPlaybackState) == 0x78 ? 1 : -1];
typedef char PlaybackStateKeyOffset[(u32) & ((Recovered_PlaybackState*)0)->poolKey == 0x28 ? 1 : -1];
typedef char PlaybackStateClaimedOffset[(u32) & ((Recovered_PlaybackState*)0)->claimed == 0x66 ? 1 : -1];
typedef char ExtendedStateCountOffset[(u32) & ((Recovered_PlaybackStatePool*)0)->extendedStateCount == 0xC ? 1 : -1];

Recovered_PlaybackState* PlaybackStatePool_Acquire(Recovered_PlaybackStatePool* self, u64 key);
Recovered_PlaybackState* PlaybackStatePool_AcquireExtended(Recovered_PlaybackStatePool* self, u64 key);
void PlaybackStatePool_Release(Recovered_PlaybackStatePool* self, Recovered_PlaybackState* state);
void PlaybackStatePool_ReleaseExtended(Recovered_PlaybackStatePool* self, Recovered_PlaybackState* state);
#endif
