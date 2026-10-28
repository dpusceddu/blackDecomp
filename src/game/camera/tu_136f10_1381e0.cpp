#include "game/actor/bone_cache.h"
extern "C" {
extern s32 func_00138298(Recovered_ActorBoneCache*, const char*);
extern const char* D_003BCE70[11];
extern const f32 D_003F5128[4] __attribute__((section(".rodata.bone_defaults"))) = {0.0f, 5.0f, 12.0f, 22.0f};
extern void func_001415A8(void*, s32);
s32 func_001381E0(Recovered_ActorBoneCache* cache) {
    const char** name = D_003BCE70;
    s32* index = cache->indices;
    s32 remaining = 10;
    do {
        if (*name) *index = func_00138298(cache, *name);
        ++index;
        --remaining;
        ++name;
    } while (remaining >= 0);
    if (cache->catalog) {
        const f32* source = D_003F5128;
        f32* target = cache->catalog->unk_28;
        s32 remaining = 3;
        do {
            *target = *source;
            --remaining;
            ++source;
            ++target;
        } while (remaining >= 0);
    }
    cache->unk_38 = 0;
    func_001415A8(cache->unk_3C, cache->unk_04);
    return 1;
}
}
