#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
#include "sony/memory_card.h"
extern Recovered_MemoryCardSuperblock D_003D6348[];
extern Recovered_MemoryCardCache D_0047A1C0[];
extern s32 MemoryCard_ReadClusters(s32, void*, s32, s32);
extern s32 MemoryCard_WriteClusters(s32, void*, s32, s32);

s32 MemoryCard_FlushCache(s32 index) {
    s32* count;
    s32* first;
    s32 firstCluster;
    s32 cacheOffset;
    s32 result;

    cacheOffset = index * sizeof(Recovered_MemoryCardCache);
    first = (void*)(cacheOffset + (s32)D_0047A1C0);
    firstCluster = *first;
    result = 1;
    if (firstCluster != -1) {
        count = (void*)(cacheOffset + (s32)&D_0047A1C0[0].count);
        result =
            MemoryCard_WriteClusters(index, (void*)(cacheOffset + (s32)&D_0047A1C0[0].clusters), firstCluster, *count);
        *first = -1;
        *count = 0;
    }
    return result;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35a990_35ace0", func_0035AD50);
#ifdef NON_MATCHING
// Unmatched: one cache/cluster byte-offset addition has reversed operands.
s32 MemoryCard_ReadCachedCluster(s32 index, Recovered_MemoryCardCluster* output, s32 unit) {
    s32 cacheOffset = index * sizeof(Recovered_MemoryCardCache);
    s32 firstUnit =
        unit + ((Recovered_MemoryCardSuperblock*)(index * sizeof(Recovered_MemoryCardSuperblock) + (u32)D_003D6348))
                   ->allocOffset;
    if (firstUnit >= D_0047A1C0[index].firstCluster &&
        firstUnit < D_0047A1C0[index].firstCluster + D_0047A1C0[index].count) {
        *output = *(Recovered_MemoryCardCluster*)((firstUnit - D_0047A1C0[index].firstCluster) *
                                                      (s32)sizeof(Recovered_MemoryCardCluster) +
                                                  cacheOffset + (u32)&D_0047A1C0[0].clusters);
        return 1;
    }
    return MemoryCard_ReadClusters(index, output, firstUnit, 1);
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35a990_35ace0", func_0035B0E8);
#endif

s32 MemoryCard_IsBadBlock(s32 index, s32 block) {
    Recovered_MemoryCardSuperblock* record = (void*)(index * sizeof(Recovered_MemoryCardSuperblock) + (u32)D_003D6348);
    s32 i;
    for (i = 0; i < 32; i++) {
        if (record->badBlocks[i] == block) { return 1; }
    }
    return 0;
}

#ifdef NON_MATCHING
// Unmatched: Sony keeps mflo before jal; modern gas changes the zero-divisor trap encoding.
s32 MemoryCard_IsBadCluster(s32 index, s32 unit) {
    return MemoryCard_IsBadBlock(index, unit * D_003D6348[index].pagesPerCluster / D_003D6348[index].pagesPerBlock);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35a990_35ace0", func_0035B2B0);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35a990_35ace0", func_0035B2F8);
