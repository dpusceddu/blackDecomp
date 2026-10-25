// Partial PS2 volume view; class identity, allocation and complete hierarchy remain unverified.
// Exact debug drawing verifies receiver130/140/150 and three128-bit geometry/color arguments.
// Exact OnceVolume::SignalOnce verifies flags195/196 and inherited virtual slot1 at vptr10.
#ifndef BLACK_ACTOR_VOLUME_STATE_HPP
#define BLACK_ACTOR_VOLUME_STATE_HPP
#include "game/actor/region_state.hpp"
namespace ActorParts {
class VolumeBounds:public RegionInterface {
public:
 char toBounds[0x11C];Position4 upper,lower;Matrix4 world;
};
class SimpleVolume:public VolumeBounds {
public:void Debug();
};
class CrossingVolume:public VolumeBounds {
public:void Debug();
};
class OnceVolume:public VolumeBounds {
public:
 char toFired[5];unsigned char fired,result;
 void SignalOnce(long);void Debug();
};
}
#endif
