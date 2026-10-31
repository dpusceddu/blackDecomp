#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_0040A718[];
const char rodata_0040A718[120] __asm__("D_0040A718") __attribute__((aligned(8))) = "%s" "\000\000\000\000\000\000" "addr: 0x%08x%c" "\000\000" "size: %10u (%8x)%c" "\000\000\000\000\000\000" "data: %s%c" "\000\000\000\000\000\000" "attr: %s %s%c" "\000\000\000" "internal" "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000" "mapped" "\000\000\000\000\000\000\000\000\000\000";

/* Partial chunk header shared by the boundary predicate; original identities are UNVERIFIED. */
typedef struct {
    u32 unk_00;
    u32 sizeAndFlags;
} Recovered_HeapChunk;

extern s32 func_003535E0(void*, s32, u32, s32);
extern void func_003535B0(s32, void*, s32);
extern s32 func_003534A8(void*, Recovered_HeapChunk*);
extern s32 func_003550E8(void*, s32);

extern s8* func_00353758(void*, s32, s32);
extern void* func_0035C6EC(void*, s32, u32);

extern s32 func_00352F30(void*, void*, s32, s32, s32, s32, s32);

extern s32 func_0036A038();

void func_00353700(s32 arg0) {
    func_0036A038(D_0040A718, arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_353118_353700", func_00353728);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_353118_353700", func_00353758);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_353118_353700", func_00353F50);
void func_00353FB0(void* heap, s8* memory) {
    s32 flags;
    s32 previousSize;
    s32 nextSize;
    s8** binSlot;
    s8* top;
    s8* tail;
    s8* next;
    s8* chunk;
    u32 size;
    void* bin;

    if (memory != NULL) {
        chunk = (s8*)(((s8*)memory) + -8);
        size = M2C_FIELD(chunk, s32*, 4) & 0x7FFFFFF8;
        if (((u32)M2C_FIELD(heap, u32*, 4) >= size) && (func_003535E0(heap, 0, (u32)chunk, (s32)size) != 0)) {
            binSlot = (s8**)(((s8*)heap) + (size >> 1));
            M2C_FIELD(heap, u32*, 4) = (u32)(M2C_FIELD(heap, u32*, 4) | 1);
            M2C_FIELD(chunk, s8**, 0xC) = (s8*)*binSlot;
            M2C_FIELD(chunk, s32*, 4) = (s32)(M2C_FIELD(chunk, s32*, 4) | 0x80000004);
            *binSlot = chunk;
        } else {
            flags = M2C_FIELD(chunk, s32*, 4);
            if (!(flags & 2)) {
                next = &chunk[size];
                nextSize = M2C_FIELD(next, s32*, 4) & 0x7FFFFFF8;
                if (!(flags & 1)) {
                    previousSize = M2C_FIELD(chunk, s32*, 0);
                    size += previousSize;
                    chunk = (s8*)(((s8*)chunk) - previousSize);
                    M2C_FIELD(chunk, s32*, 4) = (s32)(size | 1);
                    M2C_FIELD(next, u32*, 0) = size;
                    M2C_FIELD(M2C_FIELD(chunk, void**, 8), void**, 0xC) = (void*)M2C_FIELD(chunk, void**, 0xC);
                    M2C_FIELD(M2C_FIELD(chunk, void**, 0xC), void**, 8) = (void*)M2C_FIELD(chunk, void**, 8);
                }
                if (M2C_FIELD(&next[nextSize], s32*, 4) & 1) {
                    M2C_FIELD(next, u32*, 0) = size;
                    M2C_FIELD(next, s32*, 4) = (s32)(M2C_FIELD(next, s32*, 4) & 0xFFFFFFFE);
                } else {
                    size += nextSize;
                    M2C_FIELD(M2C_FIELD(next, void**, 8), void**, 0xC) = (void*)M2C_FIELD(next, void**, 0xC);
                    M2C_FIELD(M2C_FIELD(next, void**, 0xC), void**, 8) = (void*)M2C_FIELD(next, void**, 8);
                    M2C_FIELD(chunk, s32*, 4) = (s32)(size | 1);
                    M2C_FIELD(chunk + size, u32*, 0) = size;
                }
                top = M2C_FIELD(heap, s8**, 0x440);
                if ((chunk != top) && (next != top)) {
                    bin = (u8*)heap + 0x30;
                    tail = M2C_FIELD(bin, s8**, 0xC);
                    M2C_FIELD(chunk, void**, 8) = bin;
                    M2C_FIELD(chunk, s8**, 0xC) = tail;
                    M2C_FIELD(bin, s8**, 0xC) = chunk;
                    M2C_FIELD(tail, s8**, 8) = chunk;
                } else {
                    M2C_FIELD(heap, s8**, 0x440) = chunk;
                    func_003535B0((s32)heap, chunk, (s32)size);
                }
                if (size > 0xFFFFU) {
                    if (func_003534A8(heap, (Recovered_HeapChunk*)&chunk[size]) != 0) {
                        if (size >= (u32)M2C_FIELD(heap, u32*, 0x4D8)) {
                            func_003550E8(heap, M2C_FIELD(heap, s32*, 0x4DC));
                        }
                    }
                }
            }
        }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_353118_353700", func_00354190);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_353118_353700", func_00354228);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_353118_353700", func_00354628);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_353118_353700", func_00354630);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_353118_353700", func_00354968);
#ifdef NON_MATCHING
// Unmatched: body matches; jump-table placement interleaves diagnostics and the assembly-backed realloc table.
s8* func_00354970(void* heap, s32 count, s32 size, s32 flags) {
    u32 chunkSize;
    s64 bytes;
    s8* memory;
    s8* cursor;
    u64 words;

    memory = func_00353758(heap, count * size, flags);
    if (memory != NULL) {
        chunkSize = M2C_FIELD(memory, s32*, -4) & 0x7FFFFFF8;
        bytes = (s64)chunkSize - 4;
        if (bytes >= 0x21) {
            func_0035C6EC((s32)memory, 0, chunkSize - 4);
        } else {
            words = bytes / 4 - 1;
            cursor = memory;
            switch (words) {
                case 7:
                    M2C_FIELD(memory, s32*, 0) = 0;
                    cursor = (s8*)(((s8*)memory) + 4);
                    /* fallthrough */
                case 6:
                    M2C_FIELD(cursor, s32*, 0) = 0;
                    cursor = (s8*)(((s8*)cursor) + 4);
                    /* fallthrough */
                case 5:
                    M2C_FIELD(cursor, s32*, 0) = 0;
                    cursor = (s8*)(((s8*)cursor) + 4);
                    /* fallthrough */
                case 4:
                    M2C_FIELD(cursor, s32*, 0) = 0;
                    cursor = (s8*)(((s8*)cursor) + 4);
                    /* fallthrough */
                case 3:
                    M2C_FIELD(cursor, s32*, 0) = 0;
                    cursor = (s8*)(((s8*)cursor) + 4);
                    /* fallthrough */
                case 2:
                    M2C_FIELD(cursor, s32*, 0) = 0;
                    cursor = (s8*)(((s8*)cursor) + 4);
                    /* fallthrough */
                case 1:
                    M2C_FIELD(cursor, s32*, 0) = 0;
                    cursor = (s8*)(((s8*)cursor) + 4);
                    /* fallthrough */
                case 0: M2C_FIELD(cursor, s32*, 0) = 0; break;
            }
        }
    }
    return memory;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_353118_353700", func_00354970);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_353118_353700", func_00354A68);
#ifdef NON_MATCHING
// Unmatched: body matches; eight native zero tail bytes precede the next orphan fragment.
void func_00354A70(void* heap) {
    s32 flags;
    s32 previousSize;
    s32 nextSize;
    s32 originalFlags;
    s32 size;
    u32 limit;
    void** binSlot;
    void* bin;
    void* following;
    void* top;
    void* tail;
    void* next;
    void* chunk;

    limit = M2C_FIELD(heap, u32*, 4);
    if (limit != 0) {
        bin = (void*)(((s8*)heap) + 0x30);
        binSlot = (void**)(((s8*)heap) + 8);
        do {
            chunk = *binSlot;
            if (chunk != NULL) {
                *binSlot = NULL;
                do {
                    originalFlags = M2C_FIELD(chunk, s32*, 4);
                    following = M2C_FIELD(chunk, void**, 0xC);
                    flags = originalFlags & 0x7FFFFFFB;
                    M2C_FIELD(chunk, s32*, 4) = flags;
                    size = flags & 0x7FFFFFF8;
                    next = (void*)(((s8*)chunk) + size);
                    nextSize = M2C_FIELD(next, s32*, 4) & 0x7FFFFFF8;
                    if (!(originalFlags & 1)) {
                        previousSize = M2C_FIELD(chunk, s32*, 0);
                        size += previousSize;
                        chunk = (void*)(((s8*)chunk) - previousSize);
                        M2C_FIELD(chunk, s32*, 4) = (s32)(size | 1);
                        M2C_FIELD(next, s32*, 0) = size;
                        M2C_FIELD(M2C_FIELD(chunk, void**, 8), void**, 0xC) = (void*)M2C_FIELD(chunk, void**, 0xC);
                        M2C_FIELD(M2C_FIELD(chunk, void**, 0xC), void**, 8) = (void*)M2C_FIELD(chunk, void**, 8);
                    }
                    if (M2C_FIELD(((void*)(((s8*)next) + nextSize)), s32*, 4) & 1) {
                        M2C_FIELD(next, s32*, 0) = size;
                        M2C_FIELD(next, s32*, 4) = (s32)(M2C_FIELD(next, s32*, 4) & 0xFFFFFFFE);
                    } else {
                        size += nextSize;
                        M2C_FIELD(M2C_FIELD(next, void**, 8), void**, 0xC) = (void*)M2C_FIELD(next, void**, 0xC);
                        M2C_FIELD(M2C_FIELD(next, void**, 0xC), void**, 8) = (void*)M2C_FIELD(next, void**, 8);
                        M2C_FIELD(chunk, s32*, 4) = (s32)(size | 1);
                        M2C_FIELD(((s32*)(((s8*)chunk) + size)), s32*, 0) = size;
                    }
                    top = M2C_FIELD(heap, void**, 0x440);
                    if (chunk != top) {
                        if (next != top) {
                            tail = M2C_FIELD(bin, void**, 0xC);
                            M2C_FIELD(chunk, void**, 8) = bin;
                            M2C_FIELD(chunk, void**, 0xC) = tail;
                            M2C_FIELD(bin, void**, 0xC) = chunk;
                            M2C_FIELD(tail, void**, 8) = chunk;
                        } else {
                            goto block_15;
                        }
                    } else {
                    block_15:
                        M2C_FIELD(heap, void**, 0x440) = chunk;
                        func_003535B0((s32)heap, chunk, size);
                    }
                    chunk = following;
                } while (chunk != NULL);
            }
        } while (binSlot++ != ((void*)(((s8*)heap) + ((limit >> 3) * 4))));
        M2C_FIELD(heap, u32*, 4) = (u32)(M2C_FIELD(heap, u32*, 4) & 0xFFFFFFFE);
        return;
    }
    func_00352F30(heap, NULL, 0, 1, 0, 0, 0);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_353118_353700", func_00354A70);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_353118_353700", func_00354C58);
