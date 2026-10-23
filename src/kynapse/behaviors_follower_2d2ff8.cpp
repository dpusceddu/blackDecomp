#include "campaign/behaviors/follower_construction.hpp"
extern "C" BehaviorCampaign::Follower* func_002D2FF8(BehaviorCampaign::Context* context) {
    return new BehaviorCampaign::FollowerConstructible(context);
}
// Unmatched: Refresh retains two equality-result moves after vector lifetime recovery.
