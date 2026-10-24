// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_action_stack_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x181960
// PS2 0x181960; Xbox expands this stack-side action lookup.
void ActionStack::UnwindAction(Action* action)
{
    UnwindAbove(FindAction(action));
}

}  // namespace BlackGame
