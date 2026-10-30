#include "ps2/prelude.h"
#include "game/world_trace.hpp"
struct WorldTraceLink {
    u8 unknown00[8];
    void* geometry;
};
// The native result constructs three vector slots. Their purpose and original class are UNVERIFIED.
struct EmptyVector {
    Game::Vec value;
    EmptyVector() {}
};
struct TraceCollision {
    Game::Position4 point, normal;
    EmptyVector vectors[3];
    float fraction;
    u32 unknown54[3];
    WorldObjects::QueryMaterial* material;
};
typedef char TraceCollisionSize[sizeof(TraceCollision) == 0x70 ? 1 : -1];
typedef char TraceCollisionFraction[(unsigned)&((TraceCollision*)0)->fraction == 0x50 ? 1 : -1];
typedef char TraceCollisionMaterial[(unsigned)&((TraceCollision*)0)->material == 0x60 ? 1 : -1];
typedef s32 (*Visitor)(WorldObjects::QueryHit*, WorldObjects::ClosestHit*);
extern "C" void func_0027D7A0(void*, void*, Visitor, void*);
extern "C" s32 func_0027D1D8(void*, void*, TraceCollision*);
extern "C" s32 func_0012B328(WorldObjects::World* unused, WorldObjects::Region* region, WorldRayQuery* query,
                             s32 useVisitor, WorldObjects::ClosestHit* output) {
    WorldObjects::ClosestHit closest;
    TraceCollision collision;
    void* geometry = ((WorldTraceLink*)region->geometry)->geometry;
    if (useVisitor) {
        closest.unknown24 = 0;
        closest.fraction = 2.0f;
        func_0027D7A0(geometry, query, WorldObjects::World::SelectWorldHit, &closest);
        if (closest.fraction == 2.0f) return 0;
        if (closest.fraction < output->fraction) {
            *output = closest;
            return 1;
        }
    } else {
        if (func_0027D1D8(geometry, query, &collision) == 1) {
            if (collision.fraction < output->fraction) {
                output->point = collision.point;
                output->normal = collision.normal;
                output->fraction = collision.fraction;
                output->mask = collision.material->flags;
                return 1;
            }
        }
    }
    return 0;
}
