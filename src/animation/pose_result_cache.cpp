#include "include_asm.h"
#include "animation/pose_result_cache.h"
#include "animation/graph.h"
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/pose_result_cache", func_003420E8);

extern "C" int AnimationPoseCacheKey_Equals(const AnimationPoseCacheKey*,
                                            const AnimationPoseCacheKey*) __asm__("func_00394E90");
extern "C" u32 AnimationHash_Bytes(const void*, u32) __asm__("func_00352A90");
extern "C" void* AnimationCacheMemory_Set(void*, int, unsigned) __asm__("func_0035C6EC");

u32 AnimationPoseCache_Hash(const AnimationPoseCacheKey*) ANIMATION_FUNCTION(003429E8);
u32 AnimationPoseCache_Bucket(AnimationPoseResultCache*, const AnimationPoseCacheKey*) ANIMATION_FUNCTION(003426A8);
u32 AnimationPoseCache_Bucket(AnimationPoseResultCache*, const AnimationPoseCacheKey* key) {
    return AnimationPoseCache_Hash(key) >> 22;
}

void AnimationPoseCache_Clear(AnimationPoseResultCache*) ANIMATION_FUNCTION(003425E0);
#ifdef NON_MATCHING
// Unmatched: hash-chain loop shape and reset-store ordering differ.
void AnimationPoseCache_Clear(AnimationPoseResultCache* cache) {
    for (u32 index = 0; index < 1024; ++index) {
        AnimationPoseCacheEntry* entry = cache->buckets[index];
        while (entry) {
            AnimationPoseCacheEntry* next = entry->hashNext;
            entry->hashPrevious = 0;
            entry->hashNext = 0;
            entry = next;
        }
        cache->buckets[index] = 0;
    }
    AnimationPoseCacheEntry* entry = cache->usedHead;
    while (entry) {
        entry->previous = 0;
        AnimationPoseCacheEntry* next = entry->next;
        entry->next = cache->freeHead;
        cache->freeHead->previous = entry;
        cache->freeHead = entry;
        entry = next;
        ++cache->freeCount;
    }
    cache->arenaCursor = 0;
    cache->usedTail = 0;
    cache->usedHead = 0;
    cache->collisions = 0;
    cache->misses = 0;
    cache->hits = 0;
    cache->requests = 0;
    cache->usedCount = 0;
    cache->availableBytes = 0;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/pose_result_cache", func_003425E0);

AnimationPoseCacheEntry* AnimationPoseCache_Find(AnimationPoseResultCache*, u32, const AnimationPoseCacheKey*)
    ANIMATION_FUNCTION(003426C8);
AnimationPoseCacheEntry* AnimationPoseCache_Find(AnimationPoseResultCache* cache, u32 bucket,
                                                 const AnimationPoseCacheKey* key) {
    AnimationPoseCacheEntry* entry = cache->buckets[bucket];
    int found = 0;
    while (entry && !found) {
        if (AnimationPoseCacheKey_Equals(&entry->key, key))
            found = 1;
        else {
            ++cache->collisions;
            entry = entry->hashNext;
        }
    }
    return found ? entry : 0;
}

void AnimationPoseCache_InsertBucket(AnimationPoseResultCache*, AnimationPoseCacheEntry*, u32)
    ANIMATION_FUNCTION(00342758);
void AnimationPoseCache_InsertBucket(AnimationPoseResultCache* cache, AnimationPoseCacheEntry* entry, u32 bucket) {
    AnimationPoseCacheEntry* previous = cache->buckets[bucket];
    cache->buckets[bucket] = entry;
    entry->hashPrevious = 0;
    if (previous) {
        previous->hashPrevious = entry;
        entry->hashNext = previous;
    } else
        entry->hashNext = 0;
}

static inline AnimationPoseCacheEntry** BucketSlot(AnimationPoseCacheEntry** buckets, u32 index) {
    return buckets + index;
}

void AnimationPoseCache_RemoveBucket(AnimationPoseResultCache*, AnimationPoseCacheEntry*) ANIMATION_FUNCTION(00342938);
void AnimationPoseCache_RemoveBucket(AnimationPoseResultCache* cache, AnimationPoseCacheEntry* entry) {
    AnimationPoseCacheEntry** head = BucketSlot(cache->buckets, AnimationPoseCache_Bucket(cache, &entry->key));
    if (*head == entry)
        *head = entry->hashNext;
    else {
        if (entry->hashNext) entry->hashNext->hashPrevious = entry->hashPrevious;
        entry->hashPrevious->hashNext = entry->hashNext;
    }
}

AnimationPoseCacheEntry::AnimationPoseCacheEntry()
    : next(0), previous(0), key(), pose(0), bytes(0), hashNext(0), hashPrevious(0) {}

struct PackedPoseCacheKey {
    u32 clipHash;
    const void* tracks;
    u16 frame, boneCount;
    PackedPoseCacheKey(const AnimationPoseCacheKey& key) {
        AnimationCacheMemory_Set(this, 0, sizeof(*this));
        clipHash = key.clipHash;
        tracks = key.tracks;
        frame = (u16)key.frame;
        boneCount = (u16)key.boneCount;
    }
};
static inline PackedPoseCacheKey PackKey(const AnimationPoseCacheKey& key) {
    PackedPoseCacheKey packed(key);
    return packed;
}
u32 AnimationPoseCache_Hash(const AnimationPoseCacheKey* key) {
    PackedPoseCacheKey packed = PackKey(*key);
    return AnimationHash_Bytes(&packed, sizeof(packed));
}

extern u32 AnimationPoseResultCache_Vtable[] __asm__("D_003F15B8");
extern u32 AnimationPoseResultCache_BaseVtable[] __asm__("D_003F15D0");
extern AnimationPoseResultCache* AnimationPoseCache_Current __asm__("D_003F15B4");
extern "C" void AnimationCacheMemory_Delete(void*) __asm__("func_00107D48");

void AnimationPoseCache_Destroy(AnimationPoseResultCache*, int) ANIMATION_FUNCTION(00342390);
#ifdef NON_MATCHING
// Unmatched: allocator callback and entry-destruction loop lifetimes differ.
void AnimationPoseCache_Destroy(AnimationPoseResultCache* cache, int flags) {
    cache->vtable = AnimationPoseResultCache_Vtable;
    PlaybackAllocator* allocator = cache->allocator;
    allocator->vtable->free((u8*)allocator + allocator->vtable->free_adjust, cache->arena, 0);
    cache->arena = 0;
    for (u32 index = 0; index < cache->capacity; ++index) cache->entries[index].~AnimationPoseCacheEntry();
    allocator = cache->allocator;
    allocator->vtable->free((u8*)allocator + allocator->vtable->free_adjust, cache->entries, 0);
    cache->entries = 0;
    allocator = cache->allocator;
    allocator->vtable->on_remove((u8*)allocator + allocator->vtable->remove_adjust);
    cache->vtable = AnimationPoseResultCache_BaseVtable;
    AnimationPoseCache_Current = 0;
    if (flags & 1) AnimationCacheMemory_Delete(cache);
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/pose_result_cache", func_00342390);

u32 AnimationPoseCache_EvictOldest(AnimationPoseResultCache*, u32) ANIMATION_FUNCTION(003428C8);
u32 AnimationPoseCache_EvictOldest(AnimationPoseResultCache* cache, u32) {
    AnimationPoseCacheEntry* entry = cache->usedHead;
    AnimationPoseCacheEntry* next = entry->next;
    cache->usedHead = next;
    next->previous = 0;
    --cache->usedCount;
    entry->previous = 0;
    entry->next = cache->freeHead;
    cache->freeHead->previous = entry;
    cache->freeHead = entry;
    ++cache->freeCount;
    AnimationPoseCache_RemoveBucket(cache, entry);
    return entry->bytes;
}

u32 AnimationPoseCache_AllocateArena(AnimationPoseResultCache*, u32) ANIMATION_FUNCTION(00342788);
#ifdef NON_MATCHING
// Unmatched: arena-wrap and reclamation loop lifetimes differ.
u32 AnimationPoseCache_AllocateArena(AnimationPoseResultCache* cache, u32 bytes) {
    if (cache->arenaSize < cache->arenaCursor + bytes) {
        AnimationPoseCacheEntry* entry = cache->usedHead;
        while ((u32)entry->pose >= (u32)(cache->arena + cache->arenaCursor)) {
            AnimationPoseCacheEntry* next = entry->next;
            cache->usedHead = next;
            next->previous = 0;
            entry->previous = cache->usedTail;
            cache->usedTail->next = entry;
            entry->next = 0;
            cache->usedTail = entry;
            entry = cache->usedHead;
        }
        cache->availableBytes = 0;
        cache->arenaCursor = 0;
    }
    u32 reclaimed = 0;
    if (cache->availableBytes < bytes) {
        while (reclaimed + cache->availableBytes < bytes && cache->usedHead &&
               (u32)cache->usedHead->pose >= (u32)(cache->arena + cache->arenaCursor))
            reclaimed += AnimationPoseCache_EvictOldest(cache, cache->availableBytes);
        if (reclaimed) cache->availableBytes += reclaimed - bytes;
    } else
        cache->availableBytes -= bytes;
    u32 offset = cache->arenaCursor;
    cache->arenaCursor += bytes;
    return offset;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/pose_result_cache", func_00342788);

int AnimationPoseCache_Reserve(AnimationPoseResultCache*, u32, const void*, s32, s32, void**)
    ANIMATION_FUNCTION(00342478);
#ifdef NON_MATCHING
// Unmatched: cache-miss allocation and key-copy scheduling differ.
int AnimationPoseCache_Reserve(AnimationPoseResultCache* cache, u32 clipHash, const void* tracks, s32 frame,
                               s32 boneCount, void** pose) {
    AnimationPoseCacheKey key;
    key.clipHash = clipHash;
    key.tracks = tracks;
    key.frame = frame;
    key.boneCount = boneCount;
    ++cache->requests;
    u32 bucket = AnimationPoseCache_Bucket(cache, &key);
    AnimationPoseCacheEntry* entry = AnimationPoseCache_Find(cache, bucket, &key);
    int hit = entry != 0;
    if (hit)
        ++cache->hits;
    else {
        u32 bytes = 0x670 - ((50u - (u32)boneCount) << 5);
        ++cache->misses;
        u32 offset = AnimationPoseCache_AllocateArena(cache, bytes);
        entry = cache->freeHead;
        entry->pose = cache->arena + offset;
        entry->bytes = bytes;
        entry->key = key;
        cache->freeHead = entry->next;
        --cache->freeCount;
        entry->next = 0;
        entry->previous = cache->usedTail;
        if (!cache->usedHead)
            cache->usedHead = entry;
        else
            cache->usedTail->next = entry;
        cache->usedTail = entry;
        ++cache->usedCount;
        AnimationPoseCache_InsertBucket(cache, entry, bucket);
    }
    *pose = entry->pose;
    return hit;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/pose_result_cache", func_00342478);
