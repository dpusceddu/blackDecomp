#include "campaign/actor/orientation.hpp"

namespace CampaignActor {
int OrientationState::Begin(void *actor)
{
    if (started) return 1;
    active = 0;
    elapsed = 0;
    state = 0;
    previousState = 0;
    locked = 0;
    changed = 1;
    Attach(actor);
    started = 1;
    return 1;
}
// Unmatched: 0013DB40 initialization retains aggregate-load and scalar scheduling differences.
// Unmatched: 0013DC00 target assignment retains seven scalar/byte lifetime differences.
// Unmatched: 0013DF58 turn interpolation needs original matrix copy/axis-angle helper contracts.
// Unmatched: 0013EB00 look-at needs the original matrix/vector temporary stores.
// Unmatched: 0013EC38 actor attachment retains vector normalization and persistent-dot temporary differences.
}
