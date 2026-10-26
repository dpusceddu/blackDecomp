#include "include_asm.h"
#include "ps2/prelude.h"
#include "sony/memory_card.h"

extern Recovered_MemoryCardSuperblock D_003D6348[];
extern Recovered_MemoryCardScratch D_0047E200;
extern s32 func_0035BE18(s32, void*, s32, s32, s32);
extern s32 func_0035BFD0(s32, void*, s32, s32);
extern void* memset(void*, s32, u32);

s32 MemoryCard_ReadSuperblock(s32 index) {
    if (!func_0035BE18(index, D_0047E200.bytes, 0, 1, 0)) { return 0; }
    D_003D6348[index] = D_0047E200.superblock;
    return 1;
}

s32 MemoryCard_WriteSuperblock(s32 index) {
    memset(D_0047E200.bytes, 0xFF, sizeof(D_0047E200.bytes));
    D_0047E200.superblock = D_003D6348[index];
    return func_0035BFD0(index, D_0047E200.bytes, 0, 1) != 0;
}
