#include "campaign/behaviors/follower.hpp"

namespace BehaviorCampaign {
bool Follower::IsReady() {
    if (!followed) return false;
    if (limit < 0.0f) return false;
    return true;
}
// Unmatched: Configure retains different return-branch layout.
// Unmatched: Init retains different final virtual-result normalization.
// Unmatched: Refresh needs the original vector temporary and operator lifetimes.
// Unmatched: Update retains different virtual-result branch scheduling.
// Unmatched: ComputeDistance needs property-access helper and local lifetime recovery.
}
