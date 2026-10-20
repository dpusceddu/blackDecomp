// Partial PS2 effect view. Exact Update verifies world1C and receiver110/114/115.
// Semantic class identity, complete hierarchy and allocation size remain unverified.
#ifndef BLACK_CAMPAIGN_ACTOR_EXPIRY_EFFECT_HPP
#define BLACK_CAMPAIGN_ACTOR_EXPIRY_EFFECT_HPP
#include "campaign/actor/region_state.hpp"
namespace CampaignActor {
struct ExpiryWorld {char pad[0x1C];float delay;};
struct ExpiryServices {char pad[8];void*events;};
struct ExpiryServiceWorld {char pad[0xCBD8];ExpiryServices*services;};
class ExpiryEffect:public RegionInterface {
public:
 char toTimer[0xFC];float remaining;unsigned char flag1,flag2;
 void Update(float);
};
}
#endif
