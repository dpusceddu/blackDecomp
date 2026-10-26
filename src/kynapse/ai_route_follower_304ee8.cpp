#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/ai_route_follower.hpp"

// /SLUS_213.76 0x304ee8

bool AIRouteFollower::FollowPointOnly(const float* point)
{
    return FollowPoint(point, 0);
}

#ifdef NON_MATCHING
// Unmatched: vector temporary lifetimes and arithmetic scheduling differ.
extern "C" Vec3f* func_00305090(AIRouteFollower* self, const MoveRecord* move) {
    float step = move->speed / 10.0f;
    Vec3f delta, result;
    delta.Set(step * move->direction[0], step * move->direction[1], step * move->direction[2]);
    result.Set(self->position.x + delta.x, self->position.y + delta.y, self->position.z + delta.z);
    self->predicted = result;
    return &self->predicted;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/ai_route_follower_304ee8", func_00305090);
#endif
