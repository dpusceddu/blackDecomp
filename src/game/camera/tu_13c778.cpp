#include "include_asm.h"

#ifdef NON_MATCHING
// Unmatched: original damage retains15 differing instructions from vector spill/accessor scheduling.
#include "game/camera/vitals.hpp"
namespace Camera {
extern "C" {extern void *D_0040F51C,*D_0040F4BC;void func_001F28D0(void*,int,DamagePoint2*);void func_00110698(float,void*,int,int);}
void PlayerVitals::Damage(Game::Vec point,float amount){
 if(state==0&&!invulnerable){
  DamagePoint2 location;location.x=Game::X(point);location.z=Game::Z(point);
  func_001F28D0(D_0040F51C,0,&location);
  func_00110698(amount*0.0004f,D_0040F4BC,10,1);
  float next=health-amount;
  if(next<=0.0f){health=0;((DamageSink*)presentation)->Event(amount,5,point,0);}else health=next;
 }
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_13c778", func_0013C778);
#endif
