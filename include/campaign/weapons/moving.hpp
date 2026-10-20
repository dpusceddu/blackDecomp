#ifndef BLACK_CAMPAIGN_WEAPONS_MOVING_HPP
#define BLACK_CAMPAIGN_WEAPONS_MOVING_HPP
#include "campaign/weapons/instance.hpp"
#include "mod/weapons/shot.h"
namespace ModWeapons {
// Native receiver view. SOURCE controls verify only the fields they consume;
// the original C++ identity and remaining payload semantics are unverified.
struct MovingShot {
 Hit query;Position4 endpoint,origin,direction;Instance*weapon;float distance,remaining,speed;signed char flags80;unsigned char unknown81[3];float launchTime;unsigned char active,flags89,flags8a,flags8b,flags8c;unsigned char unknown8d[3];
 int Initialize(float,float,Instance*,Vec,Vec,signed char) __asm__("func_0015D3E0");
 void Update(float) __asm__("func_0015D440");
 void Recache() __asm__("func_0015D620");
 void FreshHit(Hit*) __asm__("func_0015D758");
 void NotifyOwner(Vec) __asm__("func_0015D818");
 void SetEndpoint(Vec) __asm__("func_0015D850");
 void CachedHit() __asm__("func_0015D870");
 inline Instance*Source(){return (Instance*)weapon;}
 inline Hit&Collision(){return query;}
};
typedef char MovingShotNativeStride90[sizeof(MovingShot)==0x90?1:-1];
struct MovingPool {unsigned char unknown00[0x6e0];MovingShot shots[16];int Spawn(float,float,Instance*,Vec,Vec,signed char) __asm__("func_0015D370");};
}
#endif

