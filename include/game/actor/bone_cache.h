#ifndef GAME_ACTOR_BONE_CACHE_H
#define GAME_ACTOR_BONE_CACHE_H
#include "ps2/prelude.h"

/* UNVERIFIED partial native views. The catalog's names include neck, spine and
 * limb bones; original class identities, full extents and parameter roles are unknown.
 * Accessed fields below are still confirmed only by native assembly/drafts. */
typedef struct Recovered_ActorBoneCatalog {
    u8 unk_00[0x28];
    f32 unk_28[4];
    u8 unk_38[0x24];
    s32 count;
    const char** names;
} Recovered_ActorBoneCatalog;
typedef struct Recovered_ActorBoneCache {
    Recovered_ActorBoneCatalog* catalog;
    s32 unk_04;
    u8 unk_08[4];
    s32 indices[11];
    s32 unk_38;
    void* unk_3C;
} Recovered_ActorBoneCache;

typedef char ActorBoneCatalogCountOffset[(u32)&((Recovered_ActorBoneCatalog*)0)->count == 0x5C ? 1 : -1];
typedef char ActorBoneCatalogNamesOffset[(u32)&((Recovered_ActorBoneCatalog*)0)->names == 0x60 ? 1 : -1];
typedef char ActorBoneCacheIndicesOffset[(u32)&((Recovered_ActorBoneCache*)0)->indices == 0xC ? 1 : -1];
typedef char ActorBoneCache38Offset[(u32)&((Recovered_ActorBoneCache*)0)->unk_38 == 0x38 ? 1 : -1];
typedef char ActorBoneCache3COffset[(u32)&((Recovered_ActorBoneCache*)0)->unk_3C == 0x3C ? 1 : -1];
#endif
