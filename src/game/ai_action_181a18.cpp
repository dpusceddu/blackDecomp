// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_action_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x181a18
// Unmatched: original EDX stack/ESI action contract and expanded Resolve helper.
int ActionStack::FindAction(const Action* action) const
{
    for (int index = count; index > 0;) {
        --index;
        if (action == Resolve(kinds[index])) return index;
    }
    return -1;
}

}  // namespace BlackGame
