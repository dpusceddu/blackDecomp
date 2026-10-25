#include "include_asm.h"

#include "game/weapons/moving.hpp"

namespace Weapons {
extern void*impactService __asm__("D_0040F4D4");
extern int maximumMovingIndex __asm__("D_003BCEB8");
extern "C" void func_0016E0C0(void*,Vec,Vec,BkWeaponOwnerPS2*);

static inline Position4&Vector(Position4&v){return v;}
struct ImpactIteration {signed char bounce;bool again;} __attribute__((aligned(16)));
int MovingPool::Spawn(float remaining,float speed,Instance*source,Vec origin,Vec direction,signed char flags){
 MovingShot*shot=shots;int index=0;do{if(!shot->active){if(maximumMovingIndex<index)maximumMovingIndex=index;shot->Initialize(remaining,speed,source,origin,direction,flags);return 1;}++index;++shot;}while(index<16);return 0;
}
void MovingShot::FreshHit(Hit*hit){
 ImpactIteration iteration;iteration.again=false;iteration.bounce=0;Position4 end=hit->point;
 Source()->Impact(distance,hit,&Vector(endpoint),&end,&Vector(direction),&iteration.bounce,(signed char*)&iteration.again,1,0,1,(signed char)flags80);
 if(!(flags80&2)){
  if(iteration.again){endpoint=hit->point;origin=hit->point;flags89=1;Recache();}else active=0;
 }
}
void MovingShot::NotifyOwner(Vec point){func_0016E0C0(impactService,point,Load(endpoint),Source()->weapon->owner);}
void MovingShot::CachedHit(){
 ImpactIteration iteration;iteration.again=false;iteration.bounce=0;Position4 end=Collision().point;
 if(flags8c){flags8a=func_0012AE58(frame,Sub3(Load(Collision().point),Load(direction)),Add3(Load(Collision().point),Load(direction)),2,0,1,&Collision());if(!flags8a){active=0;return;}}
 Source()->Impact(distance,&Collision(),&Vector(endpoint),&end,&Vector(direction),&iteration.bounce,(signed char*)&iteration.again,1,0,1,(signed char)flags80);
 if(iteration.again){flags89=1;endpoint=end;origin=end;Recache();}else active=0;
}
}
// Unmatched: 0015D3E0: initialization store order and frame alias context.
// Unmatched: 0015D440: motion vector and temporary scheduling.
// Unmatched: 0015D620: cached query boolean and stored-float vector helper context.

