// Ported from the companion project (an unpublished companion project), PS2 branches only.
#include "game/ai_action_stack_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x193a28
// Unmatched: Xbox expands the stack-side successor helper; private EAX contract.
void Action::RequestSuccessor(unsigned int kind, int argument)
{
    brain->stack.RequestSuccessor(this, kind, argument);
}

// /SLUS_213.76 0x193a28
// PS2 0x181810; Xbox expands this into Action::RequestSuccessor.
void ActionStack::RequestSuccessor(Action* action, unsigned int kind, int argument)
{
    int ordinal = FindAction(action);
    if (ordinal == count - 1) {
        PushAndEnter(kind, argument);
    } else if (kinds[ordinal + 1] != kind) {
        UnwindAbove(ordinal);
        PushAndEnter(kind, argument);
    }
}

}  // namespace BlackGame
