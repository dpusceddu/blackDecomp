// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_route_service_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x192560
// PS2 0x192560 and 0x192568: placeholders for policy the Xbox build compiles away.
bool AcceptAvoidance(RouteMode*, unsigned*, float*) { return false; }

// /SLUS_213.76 0x192568
void FinishFollow(RouteMode*) {}

}  // namespace BlackGame
