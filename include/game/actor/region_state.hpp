// Partial PS2 region view; semantic class identity/inheritance and allocation remain unverified.
// Exact Initialize verifies config20/21/22 and receiver0/114/118/11C/11D/120/124.
// Exact RenderBox verifies receiverD0/140/150 and three128-bit draw arguments.
#ifndef BLACK_ACTOR_REGION_STATE_HPP
#define BLACK_ACTOR_REGION_STATE_HPP
#include "ps2/matrix.hpp"
namespace ActorParts {
using namespace Game;
using Ps2Math::VU0::Matrix4;
struct RegionConfig {
 char prefix[0x10];Position4 center;
 unsigned char enabled,mode,policy;char pad23[0xD];Position4 halfExtent,color;
};
struct RegionPrefix {char prefix[0x10];};
class RegionInterface:public RegionPrefix {
public:virtual void V0();virtual void Signal(long);virtual void V2();virtual void V3();
};
class RegionState:public RegionInterface {
public:
 char toTransform[0x5C];Matrix4 transform;
 char padB0[0x20];Matrix4 world;
 void *opaque;RegionConfig *config,*source;unsigned char enabled,triggered;char pad11E[2];
 int mode,policy;char pad128[8];RegionConfig *region;char pad134[0xC];Position4 halfExtent,color;
 int Initialize(unsigned long,RegionConfig*);void RenderBox();
};
}
#endif
