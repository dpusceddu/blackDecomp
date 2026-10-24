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
