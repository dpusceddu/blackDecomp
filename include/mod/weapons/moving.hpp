#ifndef BLACK_CAMPAIGN_WEAPONS_MOVING_HPP
#define BLACK_CAMPAIGN_WEAPONS_MOVING_HPP
#include "mod/weapons/instance.hpp"
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
// 15CBA0 is the frame tick, not a constructor. It traverses 36 delayed
// records from+20 and 16 moving records from+6E0. Spawn verifies the latter.
struct MovingPool {
 void *catalog,*controllers;unsigned char *controllerFlags;Instance *instances;
 unsigned char *instanceFlags,unknown14[0xc];
 BkModDelayedShotPS2 delayed[36];MovingShot shots[16];
 int Spawn(float,float,Instance*,Vec,Vec,signed char) __asm__("func_0015D370");
};
typedef char MovingPoolDelayed20[(unsigned)&((MovingPool*)0)->delayed==0x20?1:-1];
typedef char MovingPoolShots6E0[(unsigned)&((MovingPool*)0)->shots==0x6e0?1:-1];
}
#endif
