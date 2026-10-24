#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x179cd0
// PS2 0x179cd0; the Xbox build expands it (ai_movement.hpp).

int RouteRequest::PointCount() const { return storage->count; }

}  // namespace BlackGame
