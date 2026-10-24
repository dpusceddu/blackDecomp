// Partial PS2 command views, verified by 0x162FB0 and 0x162D98. Full class identities, hierarchy
// and extents remain unverified. Opaque spans do not imply verified field types.
#ifndef BLACK_CAMPAIGN_ACTOR_COMMAND_HPP
#define BLACK_CAMPAIGN_ACTOR_COMMAND_HPP
#include "ps2/ee_types.h"
namespace CampaignActor {
struct Steering {char opaque;};
struct Drive {
 char opaque;
 void Configure(float,float,int) __asm__("func_00188B40");
};
struct WeightState {
 char prefix[0x18];float second,first;
 inline void Configure(float secondValue,float firstValue){first=firstValue;second=secondValue;}
};
struct CommandAgent {
 char prefix[0x80];int kind;char toDrive[0x20C];Drive drive;
 char toWeights[0x45F];WeightState weights;char toSteering[0x600];Steering steering;
};
struct CommandActor {
 unsigned long id;
 CommandAgent*Agent() __asm__("func_00135550");
};
struct CommandWorld {
 char prefix[0x79A4];int count;int opaque;CommandActor**actors;
};
struct ModeCommandData {
 char prefix[8];unsigned long*ids;unsigned char count;signed char mode;
};
class ModeCommand {
public:
 char prefix[0x24];ModeCommandData*data;
 void Execute();
};
struct WeightCommandData {
 char prefix[8];unsigned long*ids;unsigned char count;char opaque[3];
 float value,fraction,first,second;
};
class WeightCommand {
public:
 char prefix[0x24];WeightCommandData*data;
 void Execute();
};
}
#endif
