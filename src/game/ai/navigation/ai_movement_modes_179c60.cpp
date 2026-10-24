#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x179c60
// PS2 0x179c60; the Xbox build expands it inside RouteMode::Reset.

void RouteRequest::Clear()
{
    storage->graph = 0;
    storage->count = 0;
    startNode = 0;
    endNode = 0;
    busy = 0;
    firstPoint = 0;
    kind = 0;
}

}  // namespace BlackGame
