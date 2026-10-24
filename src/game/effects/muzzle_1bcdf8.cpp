#include "include_asm.h"

#include "game/effects/mod_muzzle.hpp"
#include "game/effects/random.hpp"
extern "C" {extern ModEffects::RandomState D_00418590;}

void ModEffects::MuzzleMethods::Advance() {
 if(phase<3) {
  if(!resource->config->quantized) {
   rotation=resource->config->extent*D_00418590.Fraction();
   if(D_00418590.Fraction()<0.5f)rotation=-rotation;
  }
  ++phase;
 }
}

#ifdef NON_MATCHING
#include "game/effects/geometry.h"
extern "C" {
extern char *D_0040F4C0,*D_0040F4D0;
extern BkEffectVectorPS2 D_004432A0;
extern BkEffectVectorPS2 *func_001A68E0(void *,int);
extern void func_0026A6F0(void *,int,f32),func_0026AA68(int),func_0026A998(int),func_0026A840(void *),func_0026A8D0(int),func_0026AEF8(s128 *),func_0026A7A0(void);
extern f32 sinf(f32),cosf(f32);
}
struct BkEffectQuadConfigPS2 {u8 prefix[0x20];void *textures[3];u32 color;int alpha[3];f32 size[3],height,angleRange;u8 fixedRotation;};
struct BkEffectQuadResourcePS2 {u8 prefix[0x10];BkEffectQuadConfigPS2 *config;};
struct BkEffectQuadVertexPS2 {BkEffectPointPS2 position;f32 u,v;u32 color,unknown;};
struct BkEffectQuadPS2 {BkEffectQuadVertexPS2 vertices[6];f32 angle;BkEffectQuadResourcePS2 *resource;s8 frame,phase;};
// Unmatched: VU I-register polynomial sine/cosine and matrix temporary lifetimes.
extern "C" void func_001BCF50(BkEffectQuadPS2 *quad) {
 int alpha=0;f32 size=0;int phase=quad->phase;
 void *render=*(void **)(D_0040F4C0+0xd540);
 if(phase>2)return;
 BkEffectQuadConfigPS2 *config=quad->resource->config;
 if(!config->textures[0])return;
 if(phase>=0&&phase<=2) {size=config->size[phase]*0.2f;alpha=config->alpha[phase];}
 if(size!=0&&alpha) {
  BkEffectPointPS2 local[4]={{size,0,0,0},{0,size,0,0},{0,0,size,0}};
  *(s128 *)&local[3]=D_004432A0;
  s128 camera[4];s128 *source=func_001A68E0(*(void **)(D_0040F4D0+0x360),5);
  for(int i=0;i<4;i++)camera[i]=source[i];
  if(*(u8 *)(*(char **)(D_0040F4D0+0x2d4)+0x108)) {
   BkEffectPointPS2 offset={0,config->height,0,0};camera[3]=BkEffectTransformPS2(camera,*(s128 *)&offset);
  }
  f32 radians=quad->angle*0.017453292f,c=cosf(radians),s=sinf(radians);
  BkEffectPointPS2 rotation[4]={{c,s,0,0},{-s,c,0,0},{0,0,1,0},{0,0,0,0}};
  s128 transform[4],combined[4];
  for(int i=0;i<3;i++)transform[i]=BkEffectRotatePS2((s128 *)rotation,*(s128 *)&local[i]);
  transform[3]=BkEffectTransformPS2((s128 *)rotation,*(s128 *)&local[3]);
  for(int i=0;i<3;i++)combined[i]=BkEffectRotatePS2(camera,transform[i]);combined[3]=BkEffectTransformPS2(camera,transform[3]);
  for(int i=0;i<6;i++) {quad->vertices[i].color=config->color;((u8 *)&quad->vertices[i].color)[3]=alpha;}
  func_0026A6F0(render,-1,0.25f);func_0026AA68(1);func_0026A998(0);func_0026A840(config->textures[quad->frame]);func_0026A8D0(1);func_0026AEF8(combined);func_0026A7A0();
 }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BCF50);
#endif
