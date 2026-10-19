#include "kynapse/point_mapper.hpp"

extern const float D_00405B60;
unsigned int PointMapper::FindTarget(PointContainer *source, PointContainer *target, const Vec3 *point) {
    unsigned int best = (unsigned int)-1;
    float bestDistance = D_00405B60;
    for (unsigned int i = 0; i < target->Count(); ++i) {
        const Vec3 *candidate = target->Get(i);
        float absolute = candidate->y-point->y;
        if (absolute<0.0f) absolute = -absolute;
        if (!(absolute>this->maxDeltaUp)) {
            float value = (candidate->z - point->z) * (candidate->z - point->z) +
                          (candidate->x - point->x) * (candidate->x - point->x) +
                          (candidate->y - point->y) * (candidate->y - point->y);
            if (!(value > bestDistance) &&
                (D_00451228.visible(point, candidate, this->entityWidth, 0, 2) & 255) &&
                value < bestDistance) {
                bestDistance = value;
                best = i;
            }
        }
    }
    return best;
}

extern const float D_00405B60 = 3.4028235e38f;
extern const float nearestPointPadding = 0.0f;
