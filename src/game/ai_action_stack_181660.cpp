// Ported from the companion project (an unpublished companion project), PS2 branches only.
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

}  // namespace BlackGame
