#ifndef GAME_WORLD_TRACE_HPP
#define GAME_WORLD_TRACE_HPP

#include "game/actor/world_objects.hpp"
#include "ps2/prelude.h"

// Shared ray-query view. Original class identity and unused result members are UNVERIFIED.
// The closest-hit callbacks also access result.point, result.normal and result.fraction.
struct WorldRayQuery {
    Game::Position4 from, to;
    u32 flags;
    void* ignore;
    u8 component;
    u8 hit;
    Weapons::Hit result;
};
typedef char WorldRayResultOffset[(unsigned)&((WorldRayQuery*)0)->result == 0x30 ? 1 : -1];
typedef char WorldRayQuerySize[sizeof(WorldRayQuery) == 0x70 ? 1 : -1];
typedef char WorldClosestHitSize[sizeof(WorldObjects::ClosestHit) == 0x40 ? 1 : -1];

extern "C" s32 func_0012AB28(WorldObjects::World*, WorldObjects::Region*, WorldRayQuery*, s32);
extern "C" s32 func_0012A918(WorldObjects::World*, WorldObjects::Region*, WorldRayQuery*, s32);

#endif
