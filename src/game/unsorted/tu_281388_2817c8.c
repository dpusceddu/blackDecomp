#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00285190(void *);

typedef struct {
    u8 unk_00[0x30];
    u16 flags;
    u8 unk_32[6];
} Recovered_PoolSlot;

typedef struct {
    u8 unk_00[0x38];
    s16 adjustment;
    u16 unk_3A;
    s32 (*available)(void *);
} Recovered_PoolVtable;

typedef struct {
    Recovered_PoolVtable *vtable;
    u8 unk_04[0x2C];
    u16 flags;
    u8 unk_32[0xA];
} Recovered_ExtendedPoolSlot;

typedef struct {
    Recovered_PoolSlot slots[64];
    Recovered_ExtendedPoolSlot extended[35];
    u8 unk_1634[0x190];
    u8 freeSlots[104];
    s32 freeCount;
} Recovered_IndexedSlotPool; /* Roles UNVERIFIED. */

s32 func_002817C8(s32 arg0) {
    s32 temp_2;
    s32 var_16;
    u32 temp_17;

    var_16 = arg0;
    temp_17 = var_16 + 0xE00;
    do {
        func_00285190((void *) var_16);
        var_16 += 0x38;
        temp_2 = (u32) var_16 < temp_17;
    } while (temp_2 != 0);
    return temp_2;
}

#ifdef NON_MATCHING
// Unmatched: virtual scan branch layout differs.
Recovered_ExtendedPoolSlot *func_00281808(Recovered_IndexedSlotPool *pool) {
    Recovered_ExtendedPoolSlot *slot = pool->extended;
    u32 index = 0;
    do {
        Recovered_PoolVtable *vtable = slot->vtable;
        if (vtable->available((u8 *)slot + vtable->adjustment)) {
            slot->flags |= 1;
            return slot;
        }
        index++;
        slot++;
    } while (index < 35);
    return 0;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_2817c8", func_00281808);

Recovered_PoolSlot *func_00281878(Recovered_IndexedSlotPool *pool) {
    s32 count = pool->freeCount;
    if (count != 0) {
        Recovered_PoolSlot *slot;
        pool->freeCount = count - 1;
        slot = (Recovered_PoolSlot *)((pool->freeSlots[count - 1] * 0x38) + (u32)pool);
        slot->flags |= 1;
        return (Recovered_PoolSlot *)((pool->freeSlots[pool->freeCount] * 0x38) + (u32)pool);
    }
    return 0;
}
