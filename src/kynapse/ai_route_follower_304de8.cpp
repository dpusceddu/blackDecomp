#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/ai_route_follower.hpp"

// /SLUS_213.76 0x304de8

bool AIRouteFollower::FollowRequest(RouteRequest* request)
{
    return FollowPoint(request->GetPoint(), request);
}
