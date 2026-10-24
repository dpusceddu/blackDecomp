#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_action_stack_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x181660
// Unmatched: private register contract and inlining of record initialization.

void ActionStack::PushAndEnter(unsigned int kind, int argument)
{
    if (kind == TopKind()) return;
    for (int index = 0; index < count; ++index)
        if (kinds[index] == kind) return;
    kinds[count] = kind;
    records[count].Reset();
    if (!count) records[count].policy.SetDefaults();
    else records[count].policy = records[count - 1].policy;
    ++count;
    Top()->Enter(argument);
    RetireFinished();
}

// /SLUS_213.76 0x181810
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

// /SLUS_213.76 0x1818a8
// Expanded into Xbox callers; PS2 0x1818a8 is out of line.
void ActionStack::Pop()
{
    Top()->Leave();
    --count;
    kinds[count] = 74;
}

}  // namespace BlackGame

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00181908);
