// Partial PS2 views verified by 0x13F160 and 0x140008. Original class identities,
// full hierarchies and allocation extents remain unverified.
#ifndef BLACK_CAMPAIGN_ACTOR_INPUT_AXIS_HPP
#define BLACK_CAMPAIGN_ACTOR_INPUT_AXIS_HPP
namespace ActorInventory7 {
struct InputAxes {
 char prefix[0x90];float lateral,forward;void*input;
 void Update();
};
struct InputBinding {
 char prefix[0x98];void*input;char toActive[0x84];unsigned char active;
 int Clear();
};
struct AxisWorld {char prefix[0x1C];float delta;};
}
#endif
