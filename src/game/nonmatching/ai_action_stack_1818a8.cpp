// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_action_stack_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x1818a8
// Expanded into Xbox callers; PS2 0x1818a8 is out of line.
void ActionStack::Pop()
{
    Top()->Leave();
    --count;
    kinds[count] = 74;
}

}  // namespace BlackGame
