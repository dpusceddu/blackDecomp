#include "include_asm.h"
#include "ps2/prelude.h"

extern void *func_00354CA0(void *, void *);

typedef struct {
    u32 unk_00;
    u32 sizeAndFlags;
} Recovered_HeapChunk;

typedef struct {
    u8 unk_00[4];
    s32 size;
} Recovered_HeapRegion; /* Heap metadata meanings UNVERIFIED. */

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_353118", func_00353118);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_353118", func_00353348);

s32 func_00353360(void) {
    return 0x1000;
}

u32 func_00353368(u32 size) {
    u32 group = size >> 6;
    u32 result = group + 0x38;
    if (group >= 33) {
        group = size >> 9;
        result = group + 0x5B;
        if (group >= 21) {
            group = size >> 12;
            result = group + 0x6E;
            if (group >= 11) {
                group = size >> 15;
                result = group + 0x77;
                if (group >= 5) {
                    u32 largest = size >> 18;
                    result = largest <= 2 ? largest + 0x7C : 0x7E;
                }
            }
        }
    }
    return result;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_353118", func_003533C8);
#ifdef NON_MATCHING
// Unmatched: chunk-boundary predicate and return scheduling differ.
s32 func_003534A8(void *heap, Recovered_HeapChunk *chunk) {
    s32 result = 0;
    if ((chunk->sizeAndFlags & 0x7FFFFFF8) < 0x10) {
        Recovered_HeapRegion *region = (Recovered_HeapRegion *)func_00354CA0(heap, chunk);
        result = 1;
        if ((u32)chunk < ((u32)region + region->size - 0x10)) {
            result = 0;
        }
    }
    return result;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_353118", func_003534A8);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_353118", func_00353510);
