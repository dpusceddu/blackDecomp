// Unmatched: 0x1a86e0: VU0 normalization and preserved vector lifetimes.
#ifdef NONMATCHING
#include "game/actor/vector_math.h"
extern char *func_00135550(void *),*func_00137AE0(char *);
extern char *func_001AB1C0(void *,char *,char *,char *,const char *,char *);
extern char *func_001AAF10(void *,char *,char *,char *,const char *,const char *,char *);
extern char *func_001A8A20(void *,char *,char *);
extern float func_0029E0D8(float),D_003BD158;
extern BkVectorPS2 D_004432C0,D_004432D0;
extern char D_003F6A40,D_003F6A48,D_003F6A50;
char *func_001A86E0(void *selector,char *name,char *actor) {
 char *movement=func_00135550(actor);float dot,angle;BkVectorPS2 direction,forward;
 if(M2C_FIELD(movement,u8 *,0x38)) {
  dot=BkSumPS2(BkMultiplyPS2(*(BkVectorPS2 *)(movement+0x60),*(BkVectorPS2 *)(actor+0x70)));
  if(dot< -D_003BD158)return func_001AB1C0(selector,name,actor+0x3b9,func_00137AE0(actor),"C_080",actor);
  if(dot>D_003BD158)return func_001AB1C0(selector,name,actor+0x3b9,func_00137AE0(actor),"C_081",actor);
 }
 if(M2C_FIELD(movement,u8 *,0x36)) {
  direction=BkNormalizePS2(*(BkVectorPS2 *)(movement+0x60));forward=BkNormalizePS2(D_004432D0);
  angle=func_0029E0D8(BkClampedDotPS2(direction,forward))*57.295780181884766f;
  if(BkSumPS2(BkMultiplyPS2(BkCrossPS2(direction,forward),D_004432C0))>0.0f)angle=-angle;
  if(__builtin_fabsf(angle)<90.0f)return func_001AAF10(selector,name,actor+0x3b9,func_00137AE0(actor),"S_372",&D_003F6A40,actor);
  return func_001AAF10(selector,name,actor+0x3b9,func_00137AE0(actor),&D_003F6A48,&D_003F6A40,actor);
 }
 if(M2C_FIELD(movement,u8 *,0x3a)) {
  if(M2C_FIELD(movement,float *,0x10)==0.0f && M2C_FIELD(actor,float *,0x2e0)>=0.1f)return func_001A8A20(selector,name,actor);
  return func_001AB1C0(selector,name,actor+0x3b9,func_00137AE0(actor),&D_003F6A40,actor);
 }
 return func_001AB1C0(selector,name,actor+0x3b9,func_00137AE0(actor),&D_003F6A50,actor);
}

#endif
