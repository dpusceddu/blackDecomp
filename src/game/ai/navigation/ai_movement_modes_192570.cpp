#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace Game {
// /SLUS_213.76 0x192570
// PS2 0x192570; the Xbox build expands it inside RouteMode::Update.

bool RouteMode::ResolveSubmitted()
{
    RouteRequest* request = active;
    bool searching = request->kind == 1;
    if (searching) return false;
    bool completed = request->kind == 9;
    if (completed) {
        AcceptCompletedRoute(this, request);
        return true;
    }
    state = ClassifyRouteResult(request);
    return false;
}

// /SLUS_213.76 0x1925d8
// Requests still being searched yield; a finished search is classified (and its route released
// when the service refused it), a completed route is accepted.
// Unmatched: mode in ESI and request expanded inline; ordinary build differs in register contract.
bool RouteMode::ResolveCurrent()
{
    int kind = active->kind;
    if (!IsSearching(kind)) {
        RouteRequest* request = active;
        bool refused = request->kind == 10;
        if (refused) {
            state = ClassifyRouteResult(request);
            ReleaseMovementRoute(this);
            return false;
        }
        bool queued = request->kind == 1;
        if (!queued) {
            AcceptCompletedRoute(this, request);
            return true;
        }
        state = ClassifyRouteResult(request);
        return false;
    }
    return false;
}

}  // namespace Game

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00192698);
