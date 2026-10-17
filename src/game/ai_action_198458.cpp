// Ported from the companion project (an unpublished companion project), PS2 branches only.
#include "game/ai_action_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x198458
void Action::LeaveMovementPermission()
{
    BaseLeave();
    if (!(Byte)phase) brain->movement->enabled = 0;
    brain->permission.SetAllowed(0);
}

}  // namespace BlackGame
