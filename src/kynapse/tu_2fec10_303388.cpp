#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "kynapse/graph/pathfinder.hpp"
#endif

#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: remaining class-call context, lifetime or scheduling differences.
float CPathFinder::RemainingDistance()
{
    if (IsComplete() == true)
        return Distance(&controller->actor->position, &target);
    float total = Distance(&controller->actor->position, &previous);
    if (previous.x != target.x || previous.y != target.y || previous.z != target.z) {
        if (waypoint != -1) {
            unsigned int next = waypoint + 1;
            if (next < route.count) {
                const Vec3f* from = &route.points[waypoint];
                const float* to = &(from + 1)->y;
                do {
                    float dz=to[1] - to[-2];
                    float dx=to[-1] - from->x;
                    ++from;
                    float dy=to[0] - to[-3];
                    to += 3;
                    ++next;
                    total += sqrtf(dz * dz + dx * dx + dy * dy);
                } while (next < route.count);
            }
        }
        total += Distance(&route.points[route.count - 1], &target);
    }
    return total;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/tu_2fec10_303388", func_00303388);
#endif
