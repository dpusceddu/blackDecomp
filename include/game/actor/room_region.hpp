// Partial region view: exact Debug verifies worldD0 and bounds130/140.
// Semantic identity, complete hierarchy, allocation and all other fields remain unverified.
#ifndef BLACK_CAMPAIGN_ACTOR_ROOM_REGION_HPP
#define BLACK_CAMPAIGN_ACTOR_ROOM_REGION_HPP
#include "game/actor/region_state.hpp"
namespace CampaignActor {
class RoomRegion:public RegionInterface {
public:
 char toWorld[0xBC];Matrix4 world;char toBounds[0x20];Position4 upper,lower;
 void Debug();
};
}
#endif
