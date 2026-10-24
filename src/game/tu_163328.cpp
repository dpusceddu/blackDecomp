#include "include_asm.h"

#ifdef NON_MATCHING
// Unmatched: 00163328: vector temporary scheduling, saved pointer allocation and FPU argument lifetime.
#include "game/weapons/delayed.hpp"
namespace ModWeapons {
struct ImpactIteration {EeS8 bounce;bool again;} __attribute__((aligned(16)));
static inline Vec ScalarVector(float x){Vec v;asm("qmtc2.ni scalarf, vectorv":"=j vectorv"(v):"r scalarf"(x));return v;}
void DelayedShotMethods::Update(float dt){
 if(active){
  Instance*source=(Instance*)weapon;
  if(!source->weapon){active=0;return;}
  BkModWeaponOwnerPS2*owner=source->weapon->owner;
  remaining-=dt;
  int player=owner->kind==2;
  if(remaining<=0.0f){
   Hit hit;ImpactIteration iteration;iteration.again=false;iteration.bounce=0;
   Position4 end;
   Vec start=Add3(point,Scale3(direction,ScalarVector((Field<float>(source->timing,0x14)-distance)-1.0f)));
   Store(end,Add3(start,Scale3(direction,ScalarVector(distance+1.0f))));
   if(func_0012AE58(frame,start,Load(end),player?0x57:0x1f,owner,1,&hit)){
    hit.fraction=1.0f-(((1.0f-hit.fraction)*distance)/Field<float>(weapon->timing,0x14));
    ((Instance*)weapon)->Impact(distance,&hit,(Position4*)&point,&end,(Position4*)&direction,&iteration.bounce,(EeS8*)&iteration.again,player,0,1,flags);
   }
   active=0;
  }
 }
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00163328);
#endif
