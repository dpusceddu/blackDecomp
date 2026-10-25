#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace Game {
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

}  // namespace Game

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001917A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191A28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191AA0);
