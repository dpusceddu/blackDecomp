#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
// Unmatched: branch merging and preserved selector/movement lifetimes.
void Selector::Stand(char* name,Actor* actor,long action) {
Movement* movement=func_00135550(actor);
 if(action==40) { Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),"S_005",actor); return; }
 if(!movement) { Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),D_003F6A00,actor);return; }
 int mode=movement->At<int>(0x80);
 if(mode==1 && *(int*)(actor->At<char*>(0x330)+0xcc)) {func_0035CBC0(name);return;}
 int family=familyIndex==-1?0:D_00414D54[familyIndex];
 const char* suffix;
 if(movement->At<unsigned char>(0x30)) suffix=D_003F69F8;
 else if(movement->At<unsigned char>(0x35)) {
  if(family==10) { if(movement->At<float>(12)>=-10.0f) {Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),"S_001",actor);return;} suffix=D_003F6A08; }
  else if(movement->At<unsigned char>(0x3a)||(mode==1 && func_0018DDD8((char*)movement+0xc94))) {Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),"S_001",actor);return;}
  else suffix=D_003F6A10;
 } else if(movement->At<unsigned char>(0x3a)) {Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),"S_001",actor);return;}
 else if(mode==1 && func_0018DDD8((char*)movement+0xc94)) suffix=D_003F6A18;
 else suffix=D_003F6A10;
 EmitFallback(name,actor->AnimationPrefix(),func_00137AE0(actor),suffix,D_003F6A00,actor);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A83A0);
#endif

#ifdef NON_MATCHING
#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
// Unmatched: branch layout and preserved receiver lifetimes.
void Selector::Move(char* name,Actor* actor) {
Movement* movement=func_00135550(actor);
 if(__builtin_fabsf(movement->At<float>(12))>0.1f && !(unsigned char)actor->HasLayer())
  Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),D_003F6A20,actor);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A8618);
#endif

#ifdef NON_MATCHING
#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
#include "ps2/prelude.h"
#include "game/actor/vector_math.h"
extern "C" void func_001A8A20(void*,char*,Actor*);
extern float D_003BD158; extern BkVectorPS2 D_004432C0,D_004432D0; extern const char D_003F6A40[],D_003F6A48[],D_003F6A50[];
// Unmatched: VU0 lifetimes, branch layout and original inline expansion remain unresolved.
void Selector::Idle(char* name,Actor* actor) {

 Movement* movement=func_00135550(actor);float dot,angle;BkVectorPS2 direction,forward;
 if(M2C_FIELD((char*)movement,u8 *,0x38)) {
  dot=SumWord(Game::Mul3(*(BkVectorPS2 *)((char*)movement+0x60),*(BkVectorPS2 *)((char*)actor+0x70)));
  if(dot< -D_003BD158)return Emit(name,(char*)actor+0x3b9,func_00137AE0(actor),"C_080",actor);
  if(dot>D_003BD158)return Emit(name,(char*)actor+0x3b9,func_00137AE0(actor),"C_081",actor);
 }
 if(M2C_FIELD((char*)movement,u8 *,0x36)) {
  direction=BkNormalizePS2(*(BkVectorPS2 *)((char*)movement+0x60));forward=BkNormalizePS2(D_004432D0);
  angle=func_0029E0D8(BkClampedDotPS2(direction,forward))*57.295780181884766f;
  if(SumWord(Game::Mul3(BkCrossPS2(direction,forward),D_004432C0))>0.0f)angle=-angle;
  if(__builtin_fabsf(angle)<90.0f)return EmitFallback(name,(char*)actor+0x3b9,func_00137AE0(actor),"S_372",D_003F6A40,actor);
  return EmitFallback(name,(char*)actor+0x3b9,func_00137AE0(actor),D_003F6A48,D_003F6A40,actor);
 }
 if(M2C_FIELD((char*)movement,u8 *,0x3a)) {
  if(M2C_FIELD((char*)movement,float *,0x10)==0.0f && M2C_FIELD((char*)actor,float *,0x2e0)>=0.1f)return func_001A8A20(this,name,actor);
  return Emit(name,(char*)actor+0x3b9,func_00137AE0(actor),D_003F6A40,actor);
 }
 return Emit(name,(char*)actor+0x3b9,func_00137AE0(actor),D_003F6A50,actor);

}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A86E0);
#endif


#ifdef NON_MATCHING
#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
// Unmatched: branch layout and preserved receiver lifetimes.
void Selector::MoveAlternate(char* name,Actor* actor,long alternate) {
if(!actor->HasLayer()) { if(!alternate)EmitFallback(name,actor->AnimationPrefix(),func_00137AE0(actor),D_003F6A80,D_0040D9C8,actor);else EmitFallback(name,actor->AnimationPrefix(),func_00137AE0(actor),D_003F6A78,D_0040D9C8,actor); }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A8D50);
#endif


#ifdef NON_MATCHING
#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
#include "ps2/prelude.h"
#include "game/actor/vector_math.h"
typedef struct {char bytes[12];} BkAnimationName12PS2;
extern float D_003BD154;extern int D_004158D8[2];extern const char D_003F68E0[],D_003F68E8[],D_003F68B8[];extern const char *D_003BD080[],*D_003BD020[],*D_003BD050[];
// Unmatched: VU0 lifetimes, branch layout and original inline expansion remain unresolved.
void Selector::Action(char* name,Actor* actor,int action) {

 Movement* movement=func_00135550(actor);char* motion=(char*)movement+0xa0;int backwards,state,crouching,choice;const char *suffix;float speed;unsigned int random;
 backwards=SumWord(Game::Mul3(*(BkVectorPS2 *)(motion+0x10),M2C_FIELD((char*)movement,char **,0x7c)?*(BkVectorPS2 *)(M2C_FIELD((char*)movement,char **,0x7c)+0xf0):0))<0.0f;
 state=M2C_FIELD((char*)actor,int *,0x39c);crouching=M2C_FIELD((char*)actor,u8 *,0x3aa);
 if(state==38 && func_00360838("SK_DF_S_490",M2C_FIELD((char*)actor,char **,0x330)+0x5c)==0){crouching=1;M2C_FIELD((char*)func_00135550(actor),u8 *,0x30)=1;func_00135578(actor,1);}
 choice=M2C_FIELD(func_0015D248(D_0040F4E0,func_00136B30(D_0040F4D0+0x30),0),int *,0x94)==2;
 if(!choice) {
  speed=M2C_FIELD(motion,float *,0x24);
  if(speed<D_003BD154)choice=1;
  else if(speed<D_003BD154+D_003BD154) {
   random=(D_004158D8[0]<<16)+(D_004158D8[0]>>16)+D_004158D8[1];D_004158D8[1]+=random;D_004158D8[0]=random;
   choice=0.5f<=((float)random*2.3283064365386963e-10f);
  }
 }
 switch(action) {
 case 2:suffix=backwards?"S_351":"S_350";break;
 case 3:suffix="S_356";break;
 case 11:suffix="S_322";break;
 case 4:suffix="S_377";break;
 case 5:case 8:suffix="S_377";break;
 case 6:suffix="S_471";break;
 case 7:suffix="S_476";break;
 case 9:suffix="S_330";break;
 case 10:
  if((unsigned)(M2C_FIELD(motion,int *,0x28)-7)<4)suffix=backwards?"S_345":"S_346";
  else suffix=backwards?"S_351":"S_350";
  break;
 case 1:
  if(state==40){suffix=backwards?(M2C_FIELD(motion,int *,0x28)?D_003F68E8:D_003F68E0):D_003F68B8;goto common;}
  if(choice && backwards){if(crouching)suffix="C_560";else {suffix=D_003BD080[M2C_FIELD(motion,int *,0x28)];goto common;}}
  else if(crouching)suffix="C_540";
  else {suffix=(backwards?D_003BD020:D_003BD050)[M2C_FIELD(motion,int *,0x28)];goto common;}
  break;
 default:*(BkAnimationName12PS2 *)name=*(const BkAnimationName12PS2 *)(crouching?"SH_AR_C_560":"SH_AR_S_560");return;
 }
 EmitFallback(name,(char*)actor+0x3b9,func_00137AE0(actor),suffix,D_003F68E0,actor);return;
common:EmitFallback(name,(char*)actor+0x3b9,D_003BD140,suffix,D_003F68E0,actor);

}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A8F78);
#endif

#ifdef NON_MATCHING
#include "game/graphics/animation_selector.hpp"
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A9538);
#endif

#ifdef NON_MATCHING
#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
extern "C" { extern const char D_003F6B60[];extern const char D_003F6B70[];extern const char D_003F6B78[];extern const char D_003F6B88[];extern const char D_003F6B80[];extern const char D_003F6900[];extern const char D_003F6B90[];extern const char D_003F6B68[];extern const char D_003F6BE8[];extern const char D_003F6BF0[];extern const char D_003F6BA8[];extern const char D_003F6BB0[];extern const char D_003F6BB8[];extern const char D_003F6BC0[];extern const char D_003F6BC8[];extern const char D_003F6BD0[];extern const char D_003F6BD8[];extern const char D_003F6BE0[];extern const char D_003F6E10[];extern const char D_003F6E18[];extern const char D_0040D9E8[];extern const char D_0040D9E0[];extern const char D_0040D9D8[];extern const char D_0040D9D0[]; extern const char *D_003BCFF0[],*D_003BD0B0[],*D_003BCFC0[]; }
// Unmatched: branch layout, floating-point lifetimes and original helper expansion.
void Selector::Turn(char* name,Actor* actor,long alternate,float angle) {
if(actor->HasLayer())return;
 Movement* movement=func_00135550(actor);
 if(angle<0.0f) {float magnitude=-angle;angle=-(magnitude-(float)(int)(magnitude/360.0f)*360.0f);}
 else angle-= (float)(int)(angle/360.0f)*360.0f;
 if(angle< -180.0f)angle+=360.0f;else if(angle>180.0f)angle-=360.0f;
 if(movement->At<unsigned char>(0x30)) {Emit(name,actor->AnimationPrefix(),D_003BD140,angle< -0.0f?"C_160":"C_161",actor);return;}
 const char* suffix;
 if(!movement->At<unsigned char>(0x3a)) {
  if(angle< -115.0f) {Emit(name,actor->AnimationPrefix(),D_003BD140,D_003F6BE8,actor);angle*=1.0714f;goto speed;}
  if(angle< -0.0f)suffix=D_003F6BE8;
  else if(angle>115.0f) {Emit(name,actor->AnimationPrefix(),D_003BD140,D_003F6BF0,actor);angle*=1.0714f;goto speed;}
  else suffix=D_003F6BF0;
 } else {
  if(alternate) {
   float rotation=0.0f;bool applied=false;
   if(angle< -120.0f) {Emit(name,actor->AnimationPrefix(),D_003BD140,D_003F6BA8,actor);rotation=-160.22999572753906f;applied=true;}
   else if(angle< -55.0f) {Emit(name,actor->AnimationPrefix(),D_003BD140,D_003F6BB0,actor);rotation=-61.0f;applied=true;}
   else if(angle< -0.0f)Emit(name,actor->AnimationPrefix(),D_003BD140,D_003F6BB8,actor);
   else if(angle>120.0f) {Emit(name,actor->AnimationPrefix(),D_003BD140,D_003F6BC0,actor);rotation=190.01600646972656f;applied=true;}
   else if(angle>55.0f) {Emit(name,actor->AnimationPrefix(),D_003BD140,D_003F6BC8,actor);rotation=101.2f;applied=true;}
   else Emit(name,actor->AnimationPrefix(),D_003BD140,D_003F6BD0,actor);
   if(applied && movement->At<int>(0x80)==1)movement->At<float>(0x6bc)=rotation;
   return;
  }
  if(angle< -115.0f) {Emit(name,actor->AnimationPrefix(),D_003BD140,D_003F6BD8,actor);angle*=1.0714f;goto speed;}
  if(angle< -0.0f)suffix=D_003F6BB8;
  else if(angle>115.0f) {Emit(name,actor->AnimationPrefix(),D_003BD140,D_003F6BE0,actor);angle*=1.0714f;goto speed;}
  else suffix=D_003F6BD0;
 }
 Emit(name,actor->AnimationPrefix(),D_003BD140,suffix,actor);angle*=1.6667f;
speed:
 if(movement->At<int>(0x80)==1)movement->At<float>(0x6c0)=__builtin_fabsf(angle);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A9908);
#endif


#ifdef NON_MATCHING
#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
#include "ps2/prelude.h"
#include "game/actor/vector_math.h"
extern BkVectorPS2 D_004432C0,D_004432D0;extern const char *D_003BD0E0[],*D_003BD0F8[],*D_003BD110[],*D_003BD128[];
// Unmatched: VU0 lifetimes, branch layout and original inline expansion remain unresolved.
void Selector::Aim(char* name,Actor* actor) {

 Movement* movement=func_00135550(actor);BkVectorPS2 delta,normalDelta,forward;float angle,speed;int sector;const char **table;
 BkVectorPS2 target=*(BkVectorPS2 *)((char*)movement+0x1fb0),position=*(BkVectorPS2 *)((char*)actor+0xa0);
 __asm__("vsub.xyz deltav, targetv, posv":"=j deltav"(delta):"j targetv"(target),"j posv"(position));
 normalDelta=BkNormalizePS2(delta);forward=BkNormalizePS2(D_004432D0);speed=M2C_FIELD((char*)movement,float *,0x1fa0);
 angle=func_0029E0D8(BkClampedDotPS2(normalDelta,forward))*57.295780181884766f;
 if(SumWord(Game::Mul3(BkCrossPS2(normalDelta,forward),D_004432C0))>0.0f)angle=-angle;
 angle-=M2C_FIELD((char*)movement,float *,0);
 if(angle<0.0f) {float magnitude=-angle;angle=-(magnitude-(float)(int)(magnitude/360.0f)*360.0f);}
 else angle=angle-(float)(int)(angle/360.0f)*360.0f;
 if(angle< -180.0f)angle+=360.0f;else if(angle>180.0f)angle-=360.0f;
 if(angle> -45.0f && angle<45.0f)sector=0;
 else if(angle>45.0f && angle<135.0f)sector=3;
 else {sector=1;if(angle> -135.0f && angle< -45.0f)sector=2;}
 if(speed>0.2f)table=M2C_FIELD((char*)movement,u8 *,0x30)?D_003BD0F8:D_003BD0E0;
 else table=M2C_FIELD((char*)movement,u8 *,0x30)?D_003BD128:D_003BD110;
 Emit(name,(char*)actor+0x3b9,D_003BD140,table[sector],actor);

}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A9ED0);
#endif


#ifdef NON_MATCHING
#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
extern "C" { extern const char D_003F6B60[];extern const char D_003F6B70[];extern const char D_003F6B78[];extern const char D_003F6B88[];extern const char D_003F6B80[];extern const char D_003F6900[];extern const char D_003F6B90[];extern const char D_003F6B68[];extern const char D_003F6BE8[];extern const char D_003F6BF0[];extern const char D_003F6BA8[];extern const char D_003F6BB0[];extern const char D_003F6BB8[];extern const char D_003F6BC0[];extern const char D_003F6BC8[];extern const char D_003F6BD0[];extern const char D_003F6BD8[];extern const char D_003F6BE0[];extern const char D_003F6E10[];extern const char D_003F6E18[];extern const char D_0040D9E8[];extern const char D_0040D9E0[];extern const char D_0040D9D8[];extern const char D_0040D9D0[]; extern const char *D_003BCFF0[],*D_003BD0B0[],*D_003BCFC0[]; }
// Unmatched: branch layout, floating-point lifetimes and original helper expansion.
void Selector::Sector(char* name,Actor* actor,long action,float angle) {
func_00135550(actor);
 if(angle<0.0f) {float magnitude=-angle;angle=-(magnitude-(float)(int)(magnitude/360.0f)*360.0f);}
 else angle-= (float)(int)(angle/360.0f)*360.0f;
 if(angle< -180.0f)angle+=360.0f;else if(angle>180.0f)angle-=360.0f;
 char suffix[12]; *(unsigned short*)suffix=0x5f53; suffix[2]=0;
 if(action==31)func_0035C7A4(suffix,D_003BD14C);
 else if(action==32)func_0035C7A4(suffix,D_003BD150);
 else if(action==33){func_0035C7A4(suffix,D_003F6E10);Emit(name,actor->AnimationPrefix(),D_003BD140,suffix,actor);return;}
 else if(action==34){func_0035C7A4(suffix,D_003F6E18);Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),suffix,actor);return;}
 else return;
 if(angle>=-45.0f && angle<45.0f)func_0035C7A4(suffix,D_0040D9D0);
 else if(angle>=45.0f && angle<135.0f)func_0035C7A4(suffix,D_0040D9D8);
 else if(angle>=-135.0f && angle< -45.0f)func_0035C7A4(suffix,D_0040D9E0);
 else func_0035C7A4(suffix,D_0040D9E8);
 Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),suffix,actor);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AA9D8);
#endif

#ifdef NON_MATCHING
#include "game/graphics/animation_selector.hpp"
using namespace AnimationSelectPS2;
// Unmatched: branch layout and preserved receiver lifetimes.
void Selector::Utility(char* name,Actor* actor,long alternate) {
char suffix[6];
 if(alternate)__builtin_strcpy(suffix,"U_112");else __builtin_strcpy(suffix,"U_113");
 Emit(name,actor->AnimationPrefix(),func_00137AE0(actor),suffix,actor);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AACF8);
#endif
