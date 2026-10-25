#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "kynapse/graph/pathfinder.hpp"
#endif

#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: remaining class-call context, lifetime or scheduling differences.
unsigned char __cdecl CPathFinder_AdvanceSubgoal(CPathFinder* owner)
{
    float* point = &owner->previous.x;
    if (point[0] == owner->target.x && point[1] == owner->target.y) {
        if (point[2] == owner->target.z)
            return 1;
    }
    unsigned int waypoint = owner->waypoint;
    if (waypoint > 0 && waypoint != 0xffffffff) {
        WaypointGuard* guard = owner->route.guards[waypoint - 1];
        Actor* actor = owner->controller->actor;
        if (guard) {
            if (!guard->Check(actor, &actor->position.x, point))
                return 1;
        }
    }
    unsigned int nearest = ((RouteBlock*)((char*)owner + 0x6c))->FindNearestPoint(point);
    owner->waypoint = nearest;
    if (nearest == 0xffffffff)
        return 0;
    float dz = point[2] - owner->position.z;
    float dx = point[0] - owner->position.x;
    float dy = point[1] - owner->position.y;
    float length = sqrtf(dz * dz + dx * dx + dy * dy);
    if (length < owner->heightRadiusB) {
        unsigned int next = nearest + 1;
        if (next < owner->route.count) {
            owner->waypoint = next;
            const Vec3f* waypointPoint = &owner->route.points[next];
            *point = waypointPoint->x;
            point[1] = waypointPoint->y;
            point[2] = waypointPoint->z;
        } else {
            *point = owner->target.x;
            point[1] = owner->target.y;
            point[2] = owner->target.z;
        }
        GetNameTables()->Store(owner->goalSlotIndex, owner->controller->actor);
    }
    return 1;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00302198);
#endif
