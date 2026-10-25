#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_action_stack_decls.hpp"

namespace Game {
// /SLUS_213.76 0x193af8
// Unmatched: private EAX contract and SSE floating-point comparison context.

bool Action::IsDeadlineReady() const
{
    CompletionRecord* record = Record();
    if (record->interval != -1.0f) return true;
    return record->timer.Expired();
}

// /SLUS_213.76 0x193b40
// PS2 0x193b40; Xbox expands this record lookup at each caller.
CompletionRecord* Action::Record() const
{
    int ordinal = brain->stack.FindAction(this);
    return ordinal == -1 ? 0 : &brain->stack.records[ordinal];
}

}  // namespace Game
