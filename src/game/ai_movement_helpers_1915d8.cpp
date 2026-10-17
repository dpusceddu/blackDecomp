// Ported from the companion project (an unpublished companion project), PS2 branches only.
#include "game/ai_movement_helpers_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x1915d8
// Publishes "no motion" first; when the actor strays from its route segment it escalates through
// a recovery timer and finally asks the mode to recover.
// Unmatched: inlined timer, grace and off-route expansions differ in register assignment.
void MovementModeBase::UpdateStallRecovery()
{
    heading = 0;
    speed = 0;
    stopped = 1;
    if (!bound) return;
    if (state == 5) {
        if (MoveToRouteProjection()) {
            state = 4;
            resumeTimer.Start(4.0f);
            return;
        }
        if (stallTimer.Expired() && !Recover()) state = 2;
    } else if (state == 4) {
        if (brain->stallGrace.Pending()) return;
        if (!IsOffRoute()) return;
        if (resumeTimer.Expired()) {
            state = 5;
            stallTimer.Start(2.0f);
            return;
        }
        if (!Recover()) state = 2;
    }
}

}  // namespace BlackGame
