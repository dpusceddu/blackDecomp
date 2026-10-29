#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_00281948(s32 arg0, s32 arg1);
extern void *func_002842E8(void *);
extern s32 func_00284298(void *);
extern void func_00388E30(void *, s8);
extern s32 func_002817C8(s32);

typedef struct {
    u8 unk_00[0x20];
    s16 firstAdjustment;
    u16 unk_22;
    s32 (*first)(void *);
    s16 secondAdjustment;
    u16 unk_2A;
    s32 (*second)(void *);
} Recovered_TransitionVtable;

typedef struct {
    Recovered_TransitionVtable *vtable;
    u8 unk_04[0x28];
    u8 state;
    u8 transition;
} Recovered_TransitionState;

typedef struct {
    u8 unk_00[0xCBA0];
    Recovered_TransitionVtable *vtable;
} Recovered_AudioManager; /* Layout and state roles UNVERIFIED. */

typedef struct {
    u8 unk_00[0x34];
    u8 unk_34;
} Recovered_AudioResource;

typedef struct {
    Recovered_AudioResource *resource;
    u32 age;
    u8 active;
    u8 unk_09[3];
} Recovered_AudioPoolEntry;

typedef struct {
    Recovered_AudioPoolEntry entries[48];
    s32 count;
} Recovered_AudioPool; /* Resource and flag meanings UNVERIFIED. */

void func_00280848(void *arg0) {
    func_00281948(arg0 + 0xB308, 0);
    M2C_FIELD(arg0, s8 *, 0xCB9E) = 0;
}

u8 func_00280888(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0xCB9E);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280848", func_00280898);
#ifdef NON_MATCHING
// Unmatched: virtual-call register allocation differs.
s32 func_002808A0(Recovered_AudioManager *manager) {
    Recovered_TransitionVtable *vtable = manager->vtable;
    s16 adjustment = vtable->firstAdjustment;
    s32 (*function)(void *) = vtable->first;
    function((u8 *)manager + adjustment);
    func_002817C8((s32)manager + 0xB308);
    vtable = manager->vtable;
    adjustment = vtable->secondAdjustment;
    function = vtable->second;
    return function((u8 *)manager + adjustment);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280848", func_002808A0);
#endif

void func_00280908(Recovered_TransitionState *self, s32 requested) {
    u8 state = self->state;
    switch (state) {
    case 2:
        if (requested == 0) {
            self->state = 3;
        }
        break;
    case 0: {
        Recovered_TransitionVtable *vtable = self->vtable;
        if (vtable->first((u8 *)self + vtable->firstAdjustment) != 0 && requested == 1) {
            self->state = requested;
        }
        break;
    }
    case 3:
        if (requested != 0) {
            self->state = 1;
            self->transition = 5 - self->transition;
        }
        break;
    case 1:
        if (requested != state) {
            self->state = 3;
            self->transition = 5 - self->transition;
        }
        break;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280848", func_002809F0);
s32 func_00280A38(Recovered_AudioPool *pool, Recovered_AudioResource **resources, s32 count) {
    Recovered_AudioPoolEntry *entry;
    s32 index = 0;
    pool->count = count;
    if (count > index) {
        u8 enabled = 1;
        entry = pool->entries;
        do {
            Recovered_AudioResource *resource = *resources++;
            index++;
            entry->age = 0;
            entry->resource = resource;
            resource->unk_34 = enabled;
            entry++;
        } while (index < pool->count);
    }
    return 1;
}
#ifdef NON_MATCHING
// Unmatched: compiler removes the repeated active-state check.
void func_00280A80(Recovered_AudioPool *pool) {
    s32 index = 0;
    Recovered_AudioPoolEntry *entry = pool->entries;
    while (index < pool->count) {
        if (entry->active) {
            entry->age++;
            if (entry->active && func_002842E8(entry->resource) == 0) {
                entry->active = 0;
                entry->age = 0;
            }
        }
        index++;
        entry++;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280848", func_00280A80);
#endif

#ifdef NON_MATCHING
// Unmatched: cleanup control flow and register allocation differ.
s32 func_00280B10(Recovered_AudioPool *pool) {
    s32 index = 0;
    Recovered_AudioPoolEntry *entry;
    s32 cleared;
    if (pool->count > 0) {
        entry = pool->entries;
        do {
            Recovered_AudioResource *resource = entry->resource;
            if (resource != 0) {
                if (func_00284298(resource) != 0) {
                    entry->resource = 0;
                    goto reset;
                }
                cleared = 0;
            } else {
            reset:
                func_00388E30(entry, 0);
                cleared = 1;
            }
            if (!(cleared & 0xFF)) {
                return 0;
            }
            index++;
            entry++;
        } while (index < pool->count);
    }
    pool->count = 0;
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280848", func_00280B10);
#endif

#ifdef NON_MATCHING
// Unmatched: pool scan control flow and register allocation differ.
Recovered_AudioResource *func_00280BC0(Recovered_AudioPool *pool) {
    Recovered_AudioPoolEntry *entry = pool->entries;
    u32 oldestAge = 0;
    Recovered_AudioPoolEntry *available = 0;
    s32 index = 0;
    s32 count = pool->count;
    Recovered_AudioPoolEntry *oldest = 0;
    if (count > 0) {
        do {
            if (!entry->active) {
                if (entry->resource != 0) {
                    available = entry;
                    break;
                }
            } else {
                u32 age = entry->age;
                if (oldestAge < age) {
                    oldest = entry;
                    oldestAge = age;
                } else if (oldest == 0 && age == 0) {
                    oldest = entry;
                    oldestAge = 0;
                }
            }
            index++;
            entry++;
        } while (index < count);
    }
    if (available != 0) {
        available->active = 1;
        available->age = 0;
        return available->resource;
    }
    if (oldest != 0) {
        func_00284298(oldest->resource);
        oldest->active = 1;
        oldest->age = 0;
        return oldest->resource;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_280848", func_00280BC0);
#endif
