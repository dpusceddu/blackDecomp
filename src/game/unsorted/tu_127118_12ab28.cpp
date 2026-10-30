#include "game/world_trace.hpp"
#include "ps2/prelude.h"

// Partial geometry-link views; original class identities are UNVERIFIED.
struct WorldTraceLink {
    u8 unknown00[8];
    void* geometry;
};
typedef s32 (*WorldTraceVisitor)(WorldObjects::TraceHit*, u8*);
// Traversal reports hits through the visitor and has no return-value protocol.
extern "C" void func_0027D7A0(void*, void*, WorldTraceVisitor, u8*);
extern "C" s32 func_0027DD60(void*, void*);
extern "C" s32 func_0012AB28(WorldObjects::World* unused, WorldObjects::Region* item, WorldRayQuery* trace,
                             s32 useVisitor) {
    void* geometry = ((WorldTraceLink*)item->geometry)->geometry;
    if (useVisitor) {
        u8 hit = 0;
        func_0027D7A0(geometry, trace, WorldObjects::World::MarkSolid, &hit);
        if (hit != 0) return 1;
    } else if (func_0027DD60(geometry, trace) != 0) {
        return 1;
    }
    return 0;
}
