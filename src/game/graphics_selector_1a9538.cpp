#include "campaign/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
extern "C" { extern const char D_003F6B60[];extern const char D_003F6B70[];extern const char D_003F6B78[];extern const char D_003F6B88[];extern const char D_003F6B80[];extern const char D_003F6900[];extern const char D_003F6B90[];extern const char D_003F6B68[];extern const char D_003F6BE8[];extern const char D_003F6BF0[];extern const char D_003F6BA8[];extern const char D_003F6BB0[];extern const char D_003F6BB8[];extern const char D_003F6BC0[];extern const char D_003F6BC8[];extern const char D_003F6BD0[];extern const char D_003F6BD8[];extern const char D_003F6BE0[];extern const char D_003F6E10[];extern const char D_003F6E18[];extern const char D_0040D9E8[];extern const char D_0040D9E0[];extern const char D_0040D9D8[];extern const char D_0040D9D0[]; extern const char *D_003BCFF0[],*D_003BD0B0[],*D_003BCFC0[]; }
// Unmatched: branch layout, floating-point lifetimes and original helper expansion.
void Selector::Combat(char* name,Actor* actor,long active,unsigned long variant,long action,float weight) {
int state=actor->At<int>(0x39c);
 if(action==42) {Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),D_003F6B60,actor);return;}
 if(action==43) {if(!actor->At<unsigned char>(0x3aa)){Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),D_003F6B70,actor);return;}}
 else {
  if(state==19 || state==40 || state==42) {
   if((variant&255)==255) {Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),D_003F6B78,actor);return;}
   if(state!=42) {Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),active?D_003F6B80:D_003F6B88,actor);return;}
  }
  if((variant&255)==255)variant=1;
  int actorIndex=func_00136B30(D_0040F4D0+0x30);func_0015D248(D_0040F4E0,actorIndex,0);
  unsigned long selected=variant;
  if(variant==7 || variant==9) {char* settings=func_0015D210(D_0040F4E0,actorIndex);selected=1;if(!(*(unsigned char*)(*(char**)(settings+12)+0x15)))selected=variant;}
  if(!actor->At<unsigned char>(0x3aa)) {
   const char** table;
   if(!active)table=D_003BCFF0;
   else {float threshold=actor->At<float>(0x2f8)*0.3f/100.0f;
    if(weight<=threshold)table=D_003BD0B0;
    else if(weight<=threshold || actor->At<float>(0x2f8)*0.5f/100.0f<weight)table=D_003BCFC0;
    else table=D_003BCFC0;
   }
   EmitFallback(name,actor->AnimationPrefix(),D_003BD140,table[selected],D_003F6900,actor);return;
  }
  if(weight<=actor->At<float>(0x2f8)*0.3f/100.0f)Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),D_003F6B90,actor);
  if(weight<=actor->At<float>(0x2f8)*0.3f/100.0f || actor->At<float>(0x2f8)*0.5f/100.0f<weight) {EmitFallback(name,actor->AnimationPrefix(),func_00137AE0(actor),D_003F6B68,D_003F6B90,actor);return;}
 }
 Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),D_003F6B68,actor);
}
