#ifndef SONY_MEMORY_CARD_H
#define SONY_MEMORY_CARD_H
#include "ps2/prelude.h"

/* PS2 memory-card superblock view. Field meanings agree with PS2SDK's MCDevInfo:
 * https://github.com/ps2dev/ps2sdk/blob/master/iop/memorycard/mcman/src/mcman-internal.h
 * This native record has stride 0x184 and four-byte alignment; its opaque suffix
 * is not assumed to have the IOP layout. Function names below are descriptive. */
typedef struct {
    u8 unk_00[0x2A];
    u16 pagesPerCluster;
    u16 pagesPerBlock; // UNVERIFIED: used only by the bad-cluster draft.
    u8 unk_2E[6];
    s32 allocOffset; // UNVERIFIED: cached-cluster read remains a draft.
    u8 unk_38[0x98];
    s32 badBlocks[32];
    u8 unk_150[0x34];
} __attribute__((aligned(4))) Recovered_MemoryCardSuperblock;

typedef struct {
    u32 words[256];
} Recovered_MemoryCardCluster;

typedef struct {
    s32 firstCluster;
    u8 unk_04[8];
    s32 count;
    Recovered_MemoryCardCluster clusters[8]; // UNVERIFIED: cluster copying remains a draft.
} Recovered_MemoryCardCache;

typedef union {
    Recovered_MemoryCardSuperblock superblock;
    u8 bytes[0x800];
} Recovered_MemoryCardScratch;

typedef char MemoryCardSuperblockStride[sizeof(Recovered_MemoryCardSuperblock) == 0x184 ? 1 : -1];
typedef char
    MemoryCardPagesPerClusterOffset[(u32) & ((Recovered_MemoryCardSuperblock*)0)->pagesPerCluster == 0x2A ? 1 : -1];
typedef char MemoryCardCacheStride[sizeof(Recovered_MemoryCardCache) == 0x2010 ? 1 : -1];
typedef char MemoryCardBadBlocksOffset[(u32) & ((Recovered_MemoryCardSuperblock*)0)->badBlocks == 0xD0 ? 1 : -1];

s32 MemoryCard_ReadSuperblock(s32 index);
s32 MemoryCard_WriteSuperblock(s32 index);
s32 MemoryCard_ReadClusters(s32 index, void* buffer, s32 first, s32 count);
s32 MemoryCard_WriteClusters(s32 index, void* buffer, s32 first, s32 count);
s32 MemoryCard_ReadCachedCluster(s32 index, Recovered_MemoryCardCluster* output, s32 cluster);
s32 MemoryCard_FlushCache(s32 index);
s32 MemoryCard_IsBadBlock(s32 index, s32 block);
s32 MemoryCard_IsBadCluster(s32 index, s32 cluster);
#endif
