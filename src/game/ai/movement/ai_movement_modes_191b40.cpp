#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x191b40
// PS2 0x191b40; Xbox 0x1858c0 (owner in EAX), also expanded inside both Start functions.
// Unmatched: private EAX owner contract and packed-vector arguments.

void MovementModeBase::SetSegment(PositionArg start, PositionArg end)
{
    Store(from, start);
    Store(to, end);
    stallTimer.Clear();
    resumeTimer.Clear();
}

// /SLUS_213.76 0x191b78
// PS2 0x191b78; the Xbox build expands it (ai_movement.hpp) inside UpdateStallRecovery.
bool MovementModeBase::IsOffRoute() const
{
    return 0.25f < PlanarSegmentDistance(this, Load(from), Load(to));
}

}  // namespace BlackGame
