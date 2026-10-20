#ifndef BLACK_CAMPAIGN_ACTOR_MOTION_HPP
#define BLACK_CAMPAIGN_ACTOR_MOTION_HPP
#include "classes/game/UnknownVtable_003DCA78.hpp"
#include "ps2/matrix.hpp"

namespace CampaignActor {
// Provisional owner name. The exact method verifies the C4 and 2A4 view
// accesses and the 64-byte matrix return ABI, not this class's complete layout.
struct ActorMotion : BlackPS2Classes::UnknownVtable_003DCA78 {
    BlackPS2::VU0::Matrix4 GetWorldMatrix();
    BlackPS2::VU0::Matrix4 GetLocalMatrix() __asm__("func_001357B8");
};
}
#endif
