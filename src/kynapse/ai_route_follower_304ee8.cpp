#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/ai_route_follower.hpp"

// /SLUS_213.76 0x304ee8

bool AIRouteFollower::FollowPointOnly(const float* point)
{
    return FollowPoint(point, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00305090);
