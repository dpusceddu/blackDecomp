#ifndef GAME_ACTOR_BONE_CACHE_H
#define GAME_ACTOR_BONE_CACHE_H
#include "ps2/prelude.h"

/* Exact 0x138298 confirms the catalog pointer, signed name count and name table.
 * Native names include neck, spine and limb bones. UNVERIFIED: original classes,
 * full extents, parameter roles and fields accessed only by the initializer draft. */
typedef struct Recovered_ActorBoneCatalog {
    u8 unk_00[0x28];
    f32 unk_28[4]; // UNVERIFIED: the initializer draft copies four default scalars here.
    u8 unk_38[0x24];
    s32 count;
    const char** names;
} Recovered_ActorBoneCatalog;
typedef struct Recovered_ActorBoneCache {
    Recovered_ActorBoneCatalog* catalog;
    s32 unk_04; // UNVERIFIED: forwarded by the initializer draft; original role is unknown.
    u8 unk_08[4];
    s32 indices[11]; // UNVERIFIED: the initializer draft fills these eleven bone-name slots.
    s32 unk_38; // UNVERIFIED: cleared by the initializer draft.
    void* unk_3C; // UNVERIFIED: forwarded by the initializer draft; original class is unknown.
} Recovered_ActorBoneCache;

typedef char ActorBoneCatalogCountOffset[(u32)&((Recovered_ActorBoneCatalog*)0)->count == 0x5C ? 1 : -1];
typedef char ActorBoneCatalogNamesOffset[(u32)&((Recovered_ActorBoneCatalog*)0)->names == 0x60 ? 1 : -1];
typedef char ActorBoneCacheIndicesOffset[(u32)&((Recovered_ActorBoneCache*)0)->indices == 0xC ? 1 : -1];
typedef char ActorBoneCache38Offset[(u32)&((Recovered_ActorBoneCache*)0)->unk_38 == 0x38 ? 1 : -1];
typedef char ActorBoneCache3COffset[(u32)&((Recovered_ActorBoneCache*)0)->unk_3C == 0x3C ? 1 : -1];
#endif
