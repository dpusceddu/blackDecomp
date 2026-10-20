// Partial PS2 command views, verified by 0x162FB0. Full class identities, hierarchy
// and extents remain unverified. Opaque spans do not imply verified field types.
#ifndef BLACK_CAMPAIGN_ACTOR_COMMAND_HPP
#define BLACK_CAMPAIGN_ACTOR_COMMAND_HPP
#include "ps2/ee_types.h"
namespace CampaignActor {
struct Steering {char opaque;};
struct CommandAgent {
 char prefix[0x80];int kind;char toSteering[0xC8C];Steering steering;
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
}
#endif
