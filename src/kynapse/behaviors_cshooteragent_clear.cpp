#include "kynapse/behaviors/shooter.hpp"
namespace Kaim {
bool ShooterAgent::IsClear(const Vec3* direction)
{
    if (dangerousConeAngle <= 0.0f)
        return true;
    if (!propertyA)
        return true;
    for (ActorIterator it(gEngine->actors->head); it.node; ++it) {
        if (it.node != context->actor->node && it.node != target->node) {
            Actor* actor = it.node->value;
            if ((actor->flags & gTargetFlag) && !perception->GetRecord(actor)->blocked &&
                InCone(&actor->position, &aimOrigin, direction, dangerousConeAngle, gunRange))
                return false;
        }
    }
    return true;
}
const unsigned int gTargetFlag=1;
}
