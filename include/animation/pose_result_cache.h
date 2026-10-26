#ifndef BLACK_ANIMATION_POSE_RESULT_CACHE_H
#define BLACK_ANIMATION_POSE_RESULT_CACHE_H
#include "animation/playback_state.h"

/* Native equality compares all four 32-bit fields. The hash narrows only its
   packed frame/bone-count representation; those truncations do not change equality. */
typedef struct AnimationPoseCacheKey {
    u32 clipHash;
    const void* tracks;
    s32 frame, boneCount;
#ifdef __cplusplus
    AnimationPoseCacheKey() : clipHash(0), tracks(0), frame(0), boneCount(0) {}
#endif
} AnimationPoseCacheKey;

typedef struct AnimationPoseCacheEntry {
    struct AnimationPoseCacheEntry *next, *previous;
    AnimationPoseCacheKey key;
    void* pose;
    u32 bytes;
    struct AnimationPoseCacheEntry *hashNext, *hashPrevious;
#ifdef __cplusplus
    AnimationPoseCacheEntry() __asm__("func_003429B0");
#endif
} AnimationPoseCacheEntry;

/* UNVERIFIED: original class identity, complete virtual interface, arena
   reclamation contract and statistic meanings. Names describe native accesses. */
typedef struct AnimationPoseResultCache {
    const void* vtable;
    PlaybackAllocator* allocator;
    u32 capacity;
    AnimationPoseCacheEntry *entries, *freeHead, *usedHead, *usedTail;
    u32 freeCount;
    u8* arena;
    u32 arenaSize, arenaCursor, availableBytes;
    AnimationPoseCacheEntry* buckets[1024];
    u32 usedCount, requests, hits, misses, collisions;
} AnimationPoseResultCache;

typedef char PoseCacheKeySize[sizeof(AnimationPoseCacheKey) == 16 ? 1 : -1];
typedef char PoseCacheEntrySize[sizeof(AnimationPoseCacheEntry) == 40 ? 1 : -1];
typedef char PoseCacheEntryKeyOffset[(u32) & ((AnimationPoseCacheEntry*)0)->key == 8 ? 1 : -1];
typedef char PoseCacheEntryHashOffset[(u32) & ((AnimationPoseCacheEntry*)0)->hashNext == 0x20 ? 1 : -1];
typedef char PoseResultCacheBucketsOffset[(u32) & ((AnimationPoseResultCache*)0)->buckets == 0x30 ? 1 : -1];
typedef char PoseResultCacheCountOffset[(u32) & ((AnimationPoseResultCache*)0)->usedCount == 0x1030 ? 1 : -1];
#endif
