// Partial PS2 spherical-region view. Exact Update verifies config0/10 and receiver131/134.
// Class identity, full hierarchy, allocation and remaining config fields remain unverified.
#ifndef BLACK_ACTOR_SPHERE_REGION_HPP
#define BLACK_ACTOR_SPHERE_REGION_HPP
#include "game/actor/region_state.hpp"
namespace ActorParts {
struct SphereConfig {float radius;char toCenter[0xC];Position4 center;};
class SphericalRegion:public RegionInterface {
public:
 char toFlags[0x11C];unsigned char opaque,inside;char pad132[2];SphereConfig*configuration;
 long Update(PositionArg,long);
};
}
#endif
