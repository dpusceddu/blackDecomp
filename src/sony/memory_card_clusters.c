#include "include_asm.h"
#include "ps2/prelude.h"
#include "sony/memory_card.h"

extern Recovered_MemoryCardSuperblock D_003D6348[];
extern s32 func_0035BFB0(s32, void*, s32, s32);
extern s32 func_0035BFD0(s32, void*, s32, s32);

s32 MemoryCard_ReadClusters(s32 index, void* buffer, s32 first, s32 count) {
    s32 pagesPerCluster = D_003D6348[index].pagesPerCluster;
    return func_0035BFB0(index, buffer, first * pagesPerCluster, pagesPerCluster * count);
}
s32 MemoryCard_WriteClusters(s32 index, void* buffer, s32 first, s32 count) {
    s32 pagesPerCluster = D_003D6348[index].pagesPerCluster;
    return func_0035BFD0(index, buffer, first * pagesPerCluster, pagesPerCluster * count);
}
