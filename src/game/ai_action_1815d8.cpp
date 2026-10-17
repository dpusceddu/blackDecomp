// Ported from the companion project (an unpublished companion project), PS2 branches only.
#include "game/ai_action_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x1815d8
// Unmatched: original EDI stack/EBX identity contract and callback register lifetimes.
void ActionStack::NotifyIdentityRemoved(void* identity)
{
    // Snapshot the count, but read each binding after the preceding callback.
    for (int index = count; index > 0;) {
        --index;
        Resolve(kinds[index])->IdentityRemoved(identity);
    }
}

}  // namespace BlackGame
