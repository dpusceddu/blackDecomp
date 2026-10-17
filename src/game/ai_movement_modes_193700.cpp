// Ported from the companion project (an unpublished companion project), PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x193700
// Unmatched: Xbox fills the vector members component by component; the PS2 splats a register.
bool FormationMode::Reset()
{
    bound = 0;
    return ResetBase();
}

// /SLUS_213.76 0x193720
// Unmatched: callee ContinueToGoal takes this in EAX; exact in the separate-file /GL context (link_group.py).
void FormationMode::Update()
{
    UpdateStallRecovery();
    if (state == 4) {
        if (brain->formation.subject == 0) state = 8;
        else ContinueToGoal();
    }
}

}  // namespace BlackGame
