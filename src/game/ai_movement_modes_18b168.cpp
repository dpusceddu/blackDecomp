// Ported from the companion project (an unpublished companion project), PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x18b168
// PS2 0x18b168; the Xbox build expands it (ai_movement.hpp) inside UpdateStallRecovery.
bool StallGrace::Pending() const { return !timer.Expired(); }

}  // namespace BlackGame
