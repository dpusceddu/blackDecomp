// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_movement_helpers_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x191bb8
// Unmatched: vector projection returns through a private contract; 196 vs 102 bytes.
bool MovementModeBase::MoveToRouteProjection()
{
    PositionResult projected = ProjectOntoSegment(this, Load(from), Load(to));
    float speed = FamilySpeed(&brain->familyRef);
    return RequestDestinationMotion(speed, this, ToArg(projected), false, 0.25f);
}

}  // namespace BlackGame
