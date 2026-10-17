// Ported from the companion project (an unpublished companion project).
#include "kynapse/ai_route_follower.hpp"

// /SLUS_213.76 0x304ee8
bool AIRouteFollower::FollowPointOnly(const float* point)
{
    return FollowPoint(point, 0);
}
