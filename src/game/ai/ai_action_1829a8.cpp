#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_action_decls.hpp"

namespace Game {
// /SLUS_213.76 0x1829a8
// Unmatched: the original takes its controller in EAX, returning a byte in AL.

bool Controller::IsContinuingState() const
{
    return state == 0 || state == 1 || state == 7 ||
           state == 4 || state == 5 || state == 8;
}

}  // namespace Game
