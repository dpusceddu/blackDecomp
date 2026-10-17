// Ported from the companion project (an unpublished companion project), PS2 branches only.
#include "game/ai_movement_family_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x18da40
// Unmatched: ordinary build keeps the stack argument and x87 result; exact in the separate-file /GL context.
float FamilySpeed(const FamilyRef* family)
{
    if (family->family == 42) return 2.5f;
    if (family->family == 38) return 2.5f;
    return 1.69f;
}

}  // namespace BlackGame
