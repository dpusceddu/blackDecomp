// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_action_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x197d48
void Action::LeaveReactionWait()
{
    BaseLeave();
    brain->controller.SetUpdate(1);
    brain->permission.SetAllowed(0);
    brain->reaction = 0;
}

}  // namespace BlackGame
