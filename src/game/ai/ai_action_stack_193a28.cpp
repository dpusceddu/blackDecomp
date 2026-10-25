#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_action_stack_decls.hpp"

namespace Game {
// /SLUS_213.76 0x193a28
// Unmatched: Xbox expands the stack-side successor helper; private EAX contract.

void Action::RequestSuccessor(unsigned int kind, int argument)
{
    brain->stack.RequestSuccessor(this, kind, argument);
}

}  // namespace Game

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193A58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193A60);
