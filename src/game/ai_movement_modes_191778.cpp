// Ported from the companion project (an unpublished companion project), PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x191778
// Unmatched: private register contract for the stored __m128 argument.
void MovementModeBase::Retarget(PositionArg point)
{
    Store(pending, point);
    retargeted = 1;
}

// /SLUS_213.76 0x191778
// Unmatched: private register contract and inlined submit/release expansion.
void RouteMode::Retarget(PositionArg point)
{
    if (!active) Start(point);
    MovementModeBase::Retarget(point);
    if (alternate) { alternate->Release(); alternate = 0; }
    if (active == &requests[0]) alternate = &requests[1];
    else alternate = &requests[0];
    SubmitRouteRequest(alternate, Load(target), point, true);
}

// /SLUS_213.76 0x191788
bool MovementModeBase::Recover() { return false; }

// /SLUS_213.76 0x191788
// Unmatched: private register contract (mode in EDI) and inlined resubmit expansion.
bool RouteMode::Recover()
{
    if (resubmit) {
        if (alternate) { alternate->Release(); alternate = 0; }
        resubmit = 0;
    }
    if (active && state != 8 && state != 0) {
        active->Resubmit(Load(brain->actor->position));
        state = ClassifyRouteResult(active);
        return true;
    }
    return false;
}

// /SLUS_213.76 0x191790
void MovementModeBase::Stop() { state = 0; }

// /SLUS_213.76 0x191790
void RouteMode::Stop()
{
    MovementModeBase::Stop();
    if (active) { active->Release(); active = 0; }
    if (alternate) { alternate->Release(); alternate = 0; }
    resubmit = 0;
    arrived = 0;
}

// /SLUS_213.76 0x191798
PositionResult MovementModeBase::GetTarget() const { return AsResult(target); }

// /SLUS_213.76 0x191798
// A finished route reports the point the follower is heading for, otherwise the request's
// destination (or the mode's own target when no finished route exists).
// Unmatched: hidden Vector4 return plus private EAX/ESI contract; follower call expanded.
PositionResult RouteMode::GetTarget() const
{
    if (!active) return AsResult(target);
    bool completed = active->kind == 9;
    if (!completed || arrived) return AsResult(target);
    if (state == 4 || state == 5) {
        int cursor = follower->cursor;
        if (cursor < active->PointCount()) return RoutePointAt(active, cursor);
    }
    return AsResult(active->destination);
}

}  // namespace BlackGame
