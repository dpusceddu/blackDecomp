#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_action_stack_decls.hpp"

namespace Game {
// /SLUS_213.76 0x193990
// Unmatched: expanded Record helper and private EAX action contract.

void Action::Complete(bool result)
{
    // Leave callbacks can replace bindings. Completion belongs to this record.
    CompletionRecord* record = Record();
    UnwindAbove();
    record->result = result;
    record->complete = 1;
}

// /SLUS_213.76 0x1939e0
// PS2 0x1939e0; Xbox expands the action-side unwind helper.
void Action::UnwindAbove()
{
    brain->stack.UnwindAction(this);
}

}  // namespace Game
