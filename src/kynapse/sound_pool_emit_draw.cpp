#include "include_asm.h"
#include "kynapse/agents/sound.hpp"
#include "kynapse/agents/world.hpp"
#include "kynapse/graph/node_queries.hpp"

extern KaimWorld::Engine* SoundWorld __asm__("D_003C9ED4");

namespace Kaim {
int* SoundPool::GetReservedCount(unsigned kind) {
    switch (kind) {
    case 1: return &reservedCombat;
    case 2: return &reservedWorld;
    case 4: return &reservedPlayer;
    case 32: return &reservedDanger;
    case 8: return &reservedCarcass;
    case 16: return &reservedMeat;
    case 64: return &reservedGarbage;
    default: return 0;
    }
}

} // namespace Kaim

#ifdef NON_MATCHING
namespace Kaim {
static inline bool InsertSound(SoundPool* pool, unsigned kind, const Vec3& position, int radius, Listener* owner, float duration) {
    int index = pool->ReserveSound(kind);
    if (index == -1)
        return false;
    float expiry = gNow + duration;
    *(Vec3*)&pool->events[index].x = position;
    pool->events[index].owner = owner;
    pool->events[index].category = kind;
    pool->events[index].radius = radius;
    pool->events[index].expiry = expiry;
    return true;
}

// Unmatched: floating argument save order and coordinate registers differ.
extern "C" bool func_0030E798(unsigned kind, int radius, const char* ownerName,
                               float x, float y, float z, float duration) {
    if (!gActiveSoundPool)
        return false;
    Listener* owner = 0;
    if (ownerName)
        owner = (Listener*)SoundWorld->Find(ownerName);
    return InsertSound(gActiveSoundPool, kind, Vec3(x, y, z), radius, owner, duration);
}
} // namespace Kaim
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/sound_pool_emit_draw", func_0030E798);
#endif

#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: position address register and branch scheduling differ.
void SoundPool::Draw() {
    Update();
    for (int index = activeHead; index != -1; index = events[index].next) {
        const QueryVector* position = (const QueryVector*)&events[index].x;
        if (QueryDebug.point)
            QueryDebug.point(position, 255, 255, 0);
    }
}
} // namespace Kaim
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/sound_pool_emit_draw", func_0030E8D8);
#endif
