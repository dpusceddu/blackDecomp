// Ported from the companion project (an unpublished companion project), PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x191778
// Unmatched: private register contract for the stored __m128 argument.
void MovementModeBase::Retarget(PositionArg point)
{
    Store(pending, point);
    retargeted = 1;
}

// /SLUS_213.76 0x191788
bool MovementModeBase::Recover() { return false; }

// /SLUS_213.76 0x191790
void MovementModeBase::Stop() { state = 0; }

// /SLUS_213.76 0x191798
PositionResult MovementModeBase::GetTarget() const { return AsResult(target); }

}  // namespace BlackGame
