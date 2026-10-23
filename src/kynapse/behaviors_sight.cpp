#include "context/behaviors/sight.hpp"

namespace KaimSight {

bool InSightCone(const Vec3* from, Actor* actor)
{
    if (!actor)
        return false;
    float range = 180.0f;
    FloatProperty* radius = (FloatProperty*)actor->GetAuthoredProperty(&gKeyRadius);
    if (radius)
        range = radius->value;
    Vec3 origin;
    origin = actor->position;
    Vec3 axis;
    axis = actor->extent;
    VectorProperty* position = (VectorProperty*)actor->GetAuthoredProperty(&gKeyPosition);
    if (position)
        origin = Vec3(position->value);
    VectorProperty* extent = (VectorProperty*)actor->GetAuthoredProperty(&gKeyExtent);
    if (extent)
        axis = Vec3(extent->value);
    return InCone(from, &origin, &axis, range, -1.0f);
}

}
