// Ported from the companion project (an unpublished companion project).
#include "kynapse/tracker.hpp"

namespace Kaim {
// /SLUS_213.76 0x2f4c58
Tracker::Tracker()
{
    Entity_ApplyA(gEngine, (int)TrackerOnAdded, (int)this);
    Entity_ApplyC(gEngine, (int)TrackerOnRemoved, (int)this);
    items = 0;
    count = 0;
    registry = 0;
    extras = 0;
    unknown18 = 0;
    capacity = 0;
}

}  // namespace Kaim
