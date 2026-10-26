#ifndef GAME_RESOURCE_POOL_HPP
#define GAME_RESOURCE_POOL_HPP
#include "ps2/prelude.h"

// Partial native views; the original resource classes remain unidentified.
// UNVERIFIED: unused prefixes, unknown virtual methods and reserved bytes.
typedef struct Recovered_FloatPair { float x, y; } Recovered_FloatPair;
typedef struct Recovered_FloatPairBlend {
    Recovered_FloatPair value;
    Recovered_FloatPair* target;
    float duration;
    float remaining;
} Recovered_FloatPairBlend;
typedef struct Recovered_FloatPairBank {
    u8 unk_00[0x1634];
    Recovered_FloatPairBlend blends[20];
} Recovered_FloatPairBank;
typedef char FloatPairBlendSize[sizeof(Recovered_FloatPairBlend) == 20 ? 1 : -1];
typedef char FloatPairBankBlends[(u32)&((Recovered_FloatPairBank*)0)->blends == 0x1634 ? 1 : -1];

#ifdef __cplusplus
struct Recovered_PooledResource {
    virtual void Unknown0();
    virtual void Unknown1();
    virtual s32 TryReset();
    virtual s32 IsActive(); // UNVERIFIED: this slot is used only by the Update draft.
};
struct Recovered_ResourcePoolEntry {
    Recovered_PooledResource* resource;
    u32 age;
    u8 active;
    u8 unk_09[3];
    u8 Clear();
    void Update();
};
struct Recovered_ResourcePool {
    Recovered_ResourcePoolEntry entries[16];
    s32 count;
};
typedef char ResourcePoolEntrySize[sizeof(Recovered_ResourcePoolEntry) == 12 ? 1 : -1];
typedef char ResourcePoolCount[(u32)&((Recovered_ResourcePool*)0)->count == 0xC0 ? 1 : -1];
extern "C" {
#endif
Recovered_FloatPair* FloatPairOutput_At(s32 index);
Recovered_FloatPair* FloatPairBank_GetOutput(Recovered_FloatPairBank* bank, s32 index);
void FloatPairBlend_Update(Recovered_FloatPairBlend* blend, Recovered_FloatPair* output, float elapsed);
void FloatPairBank_SetBlend(Recovered_FloatPairBank* bank, s32 index, Recovered_FloatPair* target, float duration);
void FloatPairBank_UpdateBlends(Recovered_FloatPairBank* bank, float elapsed);

#ifdef __cplusplus
void ResourcePoolEntry_SetActive(Recovered_ResourcePoolEntry* entry, s8 active);
void ResourcePool_Initialize(Recovered_ResourcePool* pool);
void ResourcePool_Update(Recovered_ResourcePool* pool);
s32 ResourcePool_Clear(Recovered_ResourcePool* pool);
Recovered_PooledResource* ResourcePool_Acquire(Recovered_ResourcePool* pool);
void ResourcePool_Rebind(Recovered_ResourcePool* pool, Recovered_PooledResource** resources, s32 count);
}
#endif
#endif
