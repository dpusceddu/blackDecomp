#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace Game {
// /SLUS_213.76 0x191568
// PS2 0x191568

void MovementModeBase::BindBase(Brain* owner)
{
    brain = owner;
    bound = 1;
}

// /SLUS_213.76 0x191578
// PS2 0x191578; the Xbox build expands it inside every Reset.
// Both vectors are marked "unset" with -6666 in x, y and z; the PS2 builds that splat once in a
// register (two pextlw) and stores the quadword to both and to a dead stack copy.
// Unmatched: the Xbox fills three components of each vector.
bool MovementModeBase::ResetBase()
{
    state = 0;
    Position4 unset;
    Store(unset, Make3(-6666.0f, -6666.0f, -6666.0f));
    Store(target, Load(unset));
    Store(pending, Load(unset));
    heading = 0;
    speed = 0;
    retargeted = 0;
    stallTimer.Clear();
    resumeTimer.Clear();
    return true;
}

}  // namespace Game
