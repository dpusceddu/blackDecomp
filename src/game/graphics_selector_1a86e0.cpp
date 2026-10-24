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
  dot=SumWord(BlackGame::Mul3(*(BkVectorPS2 *)((char*)movement+0x60),*(BkVectorPS2 *)((char*)actor+0x70)));
  if(dot< -D_003BD158)return Emit(name,(char*)actor+0x3b9,func_00137AE0(actor),"C_080",actor);
  if(dot>D_003BD158)return Emit(name,(char*)actor+0x3b9,func_00137AE0(actor),"C_081",actor);
 }
 if(M2C_FIELD((char*)movement,u8 *,0x36)) {
  direction=BkNormalizePS2(*(BkVectorPS2 *)((char*)movement+0x60));forward=BkNormalizePS2(D_004432D0);
  angle=func_0029E0D8(BkClampedDotPS2(direction,forward))*57.295780181884766f;
  if(SumWord(BlackGame::Mul3(BkCrossPS2(direction,forward),D_004432C0))>0.0f)angle=-angle;
  if(__builtin_fabsf(angle)<90.0f)return EmitFallback(name,(char*)actor+0x3b9,func_00137AE0(actor),"S_372",D_003F6A40,actor);
  return EmitFallback(name,(char*)actor+0x3b9,func_00137AE0(actor),D_003F6A48,D_003F6A40,actor);
 }
 if(M2C_FIELD((char*)movement,u8 *,0x3a)) {
  if(M2C_FIELD((char*)movement,float *,0x10)==0.0f && M2C_FIELD((char*)actor,float *,0x2e0)>=0.1f)return func_001A8A20(this,name,actor);
  return Emit(name,(char*)actor+0x3b9,func_00137AE0(actor),D_003F6A40,actor);
 }
 return Emit(name,(char*)actor+0x3b9,func_00137AE0(actor),D_003F6A50,actor);

}
