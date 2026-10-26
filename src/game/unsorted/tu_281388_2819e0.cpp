#include "game/resource_pool.hpp"
#ifdef NON_MATCHING
inline void Recovered_ResourcePoolEntry::Update() {
    if (active) {
        if (!resource->IsActive()) {
            active = 0;
            age = 0;
        }
    }
}
inline u8 Recovered_ResourcePoolEntry::Clear() {
    Recovered_ResourcePoolEntry* entry = this;
    if (entry->resource) {
        if (entry->resource->TryReset()) entry->resource = 0;
        else return 0;
    }
    ResourcePoolEntry_SetActive(entry, 0);
    return 1;
}
#endif
inline Recovered_ResourcePoolEntry& ResourcePoolEntryAt(Recovered_ResourcePool* pool, s32 index) { return pool->entries[index]; }
extern "C" {
#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00280EE0(void *, s32);

s32 func_002819E0(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 var_16;
    s32 var_4;
    u32 temp_17;

    var_16 = arg0;
    temp_17 = var_16 + 0xE00;
    var_4 = var_16;
    do {
        func_00280EE0((void *) var_4, arg1);
        var_16 += 0x38;
        temp_2 = (u32) var_16 < temp_17;
        var_4 = var_16;
    } while (temp_2 != 0);
    return temp_2;
}

void FloatPairBank_SetBlend(Recovered_FloatPairBank* bank, s32 index, Recovered_FloatPair* target, float duration) {
    bank->blends[index].value = *FloatPairBank_GetOutput(bank, index);
    bank->blends[index].target = target;
    bank->blends[index].duration = duration;
    bank->blends[index].remaining = duration;
}
void FloatPairBank_UpdateBlends(Recovered_FloatPairBank* bank, float elapsed) {
    u32 index = 0;
    Recovered_FloatPairBlend* blend = bank->blends;
    do {
        FloatPairBlend_Update(blend, FloatPairBank_GetOutput(bank, index), elapsed);
        ++index;
        ++blend;
    } while (index < 20);
}
void ResourcePool_Initialize(Recovered_ResourcePool* pool) {
    Recovered_ResourcePoolEntry* entry = pool->entries;
    Recovered_ResourcePoolEntry* end = pool->entries + 16;
    do {
        entry->resource = 0;
        entry->active = 0;
        ++entry;
    } while ((s32)entry < (s32)end);
    pool->count = 0;
}

#ifdef NON_MATCHING
// Unmatched: Inlining removes the native second active-byte check and changes loop allocation.
void ResourcePool_Update(Recovered_ResourcePool* pool) {
    s32 index = 0;
    if (pool->count > 0) {
        Recovered_ResourcePoolEntry* entry = pool->entries;
        do {
            if (entry->active) {
                ++entry->age;
                entry->Update();
            }
            ++index;
            ++entry;
        } while (index < pool->count);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_2819e0", func_00281BF8);
#endif
#ifdef NON_MATCHING
// Unmatched: Inlining coalesces the entry and iterator pointers, shortening the native frame.
s32 ResourcePool_Clear(Recovered_ResourcePool* pool) {
    s32 index = 0;
    if (pool->count > 0) {
        Recovered_ResourcePoolEntry* entry = pool->entries;
        do {
            if (!entry->Clear()) return 0;
            ++index;
            ++entry;
        } while (index < pool->count);
    }
    pool->count = 0;
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_2819e0", func_00281C98);
#endif
Recovered_PooledResource* ResourcePool_Acquire(Recovered_ResourcePool* pool) {
    Recovered_ResourcePoolEntry* available = 0;
    // Ages count active updates; equal ages select the later entry.
    u32 oldestAge = 0;
    Recovered_ResourcePoolEntry* oldest = 0;
    s32 index = 0;
    for (; index < pool->count; ++index) {
        Recovered_ResourcePoolEntry* entry = &ResourcePoolEntryAt(pool, index);
        if (entry->active == 1) {
            if (entry->age >= oldestAge) {
                oldest = entry;
                oldestAge = entry->age;
            }
        } else {
            if (entry->resource) {
                available = entry;
                break;
            }
        }
    }
    if (available) {
        Recovered_PooledResource* result = available->resource;
        available->active = 1;
        available->age = 0;
        return result;
    }
    if (oldest) {
        oldest->resource->TryReset();
        Recovered_PooledResource* result = oldest->resource;
        oldest->active = 1;
        oldest->age = 0;
        return result;
    }
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_2819e0", func_00281E20);
void ResourcePool_Rebind(Recovered_ResourcePool* pool, Recovered_PooledResource** resources, s32 count) {
    Recovered_ResourcePoolEntry* entry = pool->entries;
    for (s32 index = 0; index < 16; ++index, ++resources, ++entry) {
        if (entry->resource) {
            entry->resource->TryReset();
            if (entry->active) {
                entry->active = 0;
                entry->age = 0;
            }
        }
        if (index < count) {
            entry->resource = *resources;
            entry->age = 0;
        } else {
            entry->resource = 0;
            entry->age = 0;
        }
    }
    pool->count = count;
}

}
