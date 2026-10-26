#include "kynapse/graph/pathfinder.hpp"

namespace Kaim {
extern "C" int func_002E27F8(const float*, const float*, Actor*, int, float);
extern "C" int func_00302EE0(CPathFinder*, const float*);

unsigned char CPathFinder_AcceptActorSegment(CPathFinder* self, const float* point)
{
    if (!(unsigned char)func_002E27F8(&self->position.x, point, self->controller->actor, 2,
                                     self->radiusHolder->radius))
        return false;
    return func_00302EE0(self, point) != 1;
}
}  // namespace Kaim
