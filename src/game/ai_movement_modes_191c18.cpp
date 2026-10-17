// Ported from the companion project (an unpublished companion project), PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x191c18
bool MovementModeBase::UpdateTarget(PositionArg) { return false; }

// /SLUS_213.76 0x191c18
// Unmatched: private ESI/EAX contract and packed-vector argument copy.
bool DirectMode::UpdateTarget(PositionArg point)
{
    switch (state) {
    case 1: case 4: case 5: case 7:
        Store(target, point);
        return true;
    }
    return false;
}

// /SLUS_213.76 0x191c18
// Unmatched: private register contract (mode in EDI, point in ECX).
bool RouteMode::UpdateTarget(PositionArg point)
{
    switch (state) {
    case 1: case 7:
        return active->UpdateDestination(point);
    case 4: case 5:
        if (arrived) return false;
        if (!active->busy) return RetargetLive(this, point);
        return active->UpdateDestination(point);
    }
    return false;
}

// /SLUS_213.76 0x191c20
void RouteMode::Bind(Brain* owner)
{
    BindBase(owner);
    follower = 0;
}

}  // namespace BlackGame
