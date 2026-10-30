#include "ps2/prelude.h"
#include "ps2/vu0.hpp"
#include "game/world_trace.hpp"
extern "C" s32 func_0012A5F8(void*, s32, WorldRayQuery*);
extern "C" void func_00273708(void*, void*, s32, void*);
static inline s32 WorldRayIsDegenerate(float lengthSquared) {
    s32 small = 0;
    if (lengthSquared < 2.3283064365386963e-10f) small = 1;
    return small;
}
static inline s32 WorldRayFlag(s32 flags, s32 shift) {
    s32 result = 0;
    if ((flags >> shift) & 1) result = 1;
    return result;
}
extern "C" s32 func_0012A7C0(WorldObjects::World* self, Game::Vec from, Game::Vec to, s32 flags, void* ignore,
                             s32 component) {
    WorldRayQuery query;
    float lengthSquared = Ps2Math::VU0::ReadXWord(Game::SumSquares3(Game::Sub3(to, from)));
    if ((u8)WorldRayIsDegenerate(lengthSquared)) return 0;
    Game::Store(query.from, from);
    Game::Store(query.to, to);
    query.flags = flags;
    query.ignore = ignore;
    query.component = component;
    query.hit = 0;
    if (flags & 1) {
        s32 visitSolid = WorldRayFlag(flags, 9);
        s32 visitShapes = WorldRayFlag(flags, 8);
        int i = 0;
        WorldObjects::Region* region = self->regions;
        do {
            if (M2C_FIELD(region, u8*, 0x38)) {
                if (component) {
                    if (func_0012AB28(self, region, &query, (u8)visitSolid)) return 1;
                } else if (func_0012A918(self, region, &query, (u8)visitShapes))
                    return 1;
            }
            ++i;
            ++region;
        } while (i < 2);
    }
    if (flags & 0x6F) func_00273708(self->space, &query, (s32)func_0012A5F8, &query);
    return query.hit;
}
