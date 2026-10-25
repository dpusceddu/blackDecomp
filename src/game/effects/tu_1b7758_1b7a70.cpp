#include "include_asm.h"

#ifdef NON_MATCHING
// Unmatched: native receiver and iterator/store lifetimes remain inexact.
#include "game/effects/runtime.hpp"
#include "game/effects/geometry.h"
#include "game/effects/pool.h"
using Effects::Matrix;
extern "C" {extern char *D_0040F4D8,*D_0040F4D4;}
struct NodeManager {
 BkEffectGeometryBucketPS2 nodes[8]; void*materials[12];BkEffectGeometryBucketPS2*heads[12];
 void Clear() __asm__("func_001B8138");
 BkEffectGeometryBucketPS2 *Free(int) __asm__("func_001B82B0");
 void Add(BkEffectGeometryPS2*) __asm__("func_001B8180");
};
struct PoolMethods: BkEffectPoolPS2 {
 int Queue(void*,const Matrix*,long) __asm__("func_001B7A70");
 void Stop() __asm__("func_001B7E60");
};
extern "C" int func_001B16A8(BkEffectEntryPS2*);extern "C" void func_001B15A0(BkEffectEntryPS2*);
struct Pending {Matrix matrix;void*definition;char pad[12];};
int PoolMethods::Queue(void *definition,const Matrix *transform,long mode){
 if(pendingCount==256)return 0;
 Matrix temporary;
 if(mode==0){Effects::IdentityXYZ(temporary);temporary.row[3]=transform->row[3];}
 else if(mode==1)temporary=*transform;
 Pending *slot=(Pending*)((char*)this+0x15000)+pendingCount;
 slot->matrix=temporary;
 ((Pending*)((char*)this+0x15000))[pendingCount].definition=definition;
 pendingCount++;return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B7A70);
#endif

#ifdef NON_MATCHING
#include "game/effects/pool.h"
#include "game/effects/vector.h"
extern "C" {
extern char *D_0040F4C0,*D_0040F4C4,*D_0040F510;
extern void func_001B1168(f32,BkEffectEntryPS2 *,void *,void *,int);
extern s64 func_00108120(void *);
extern void func_001BE7F0(...),func_001B0C10(...),func_001BEBA0(...),func_0014EBE0(...),func_001BEF70(...),func_001EC158(...),func_001EC060(...);
}
// Unmatched: pending effect resource ownership and vector-valued callback signatures.
extern "C" void func_001B7B80(BkEffectPoolPS2 *pool,void *,f32 time) {
 u16 remaining=pool->pendingCount;
 while(remaining--) {
  char *pending=(char *)pool+0x15000+remaining*0x50;
  char *definition=*(char **)(pending+0x40);
  u16 index=pool->activeCount;
  BkEffectPointPS2 transform[6];
  if((u16)(pool->capacity-index)==0)break;
  pool->activeCount=index+1;
  BkEffectEntryPS2 *entry=pool->entries+pool->indices[index];
  func_001B1168(time,entry,pending,definition,0);
  /* The 64-bit sound identifier and 128-bit position are independent arguments. */
  if(*(s64 *)(definition+0x280)) {
   s64 sound=func_00108120(D_0040F4C4);
   func_001BE7F0(*(void **)(definition+0x290),0,*(u32 *)(definition+0x294),*(u32 *)(definition+0x298),*(u32 *)(definition+0x29c),(char *)pool->owner+0x83720,sound,pending);
  }
  if(definition[0x2a0])func_001B0C10(*(u32 *)(definition+0x2a4),*(u32 *)(definition+0x2a8),0,D_0040F4C0+0xd290,*(s64 *)(definition+0x2b0));
  if(definition[0x242])func_001BEBA0(0,10.0f,(char *)pool->owner+0x83d24,entry,definition);
  u16 slot=*(u16 *)(definition+0x240);
  if(slot!=9999) {
   char *table=*(char **)((char *)pool->resource+0x20)+slot*0x48;
   if(*(s64 *)table!=(s64)0x9b5db9da662d3b18ULL) {
    func_0014EBE0(transform,pending,table);
   }else func_001BEF70((char *)pool->owner+0x83fb0,*(s128 *)(pending+0x30));
  }
  s8 category=definition[0x270];void *service=*(void **)(*(char **)(D_0040F510+0xcbd8)+0x24);
  if(category>0)func_001EC158(service,category,*(s128 *)(pending+0x30));
  if(*(f32 *)(definition+0x278)>0)func_001EC060(*(u32 *)(definition+0x274),service,*(s128 *)(pending+0x30),0,0);
 }
 pool->pendingCount=0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B7B80);
#endif

#ifdef NON_MATCHING
// Unmatched: native receiver and iterator/store lifetimes remain inexact.
#include "game/effects/runtime.hpp"
#include "game/effects/geometry.h"
#include "game/effects/pool.h"
using Effects::Matrix;
extern "C" {extern char *D_0040F4D8,*D_0040F4D4;}
struct NodeManager {
 BkEffectGeometryBucketPS2 nodes[8]; void*materials[12];BkEffectGeometryBucketPS2*heads[12];
 void Clear() __asm__("func_001B8138");
 BkEffectGeometryBucketPS2 *Free(int) __asm__("func_001B82B0");
 void Add(BkEffectGeometryPS2*) __asm__("func_001B8180");
};
struct PoolMethods: BkEffectPoolPS2 {
 int Queue(void*,const Matrix*,long) __asm__("func_001B7A70");
 void Stop() __asm__("func_001B7E60");
};
extern "C" int func_001B16A8(BkEffectEntryPS2*);extern "C" void func_001B15A0(BkEffectEntryPS2*);
struct Pending {Matrix matrix;void*definition;char pad[12];};
void PoolMethods::Stop(){struct Book {unsigned short *indices,*reverse;unsigned short activeCount;};Book *book=(Book*)((char*)this+0x1a000);unsigned short remaining=book->activeCount-1,*cursor=book->indices;while(remaining!=65535){BkEffectEntryPS2 *entry=entries+*cursor;if(func_001B16A8(entry))func_001B15A0(entry);--remaining;++cursor;}}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B7E60);
#endif


#ifdef NON_MATCHING
#include "game/effects/geometry.h"
struct BkEffectDrawPacketPS2 { BkEffectVectorPS2 normal,points[4];BkEffectUVPS2 uv[4]; };
extern "C" void func_001C45C0(void),func_001C4148(void *),func_001C41D0(void *),func_001C43F0(void *);
// Unmatched: matrix temporary lifetimes and original empty vector-constructor loops.
extern "C" void func_001B82E0(char *buckets,u32 pass) {
 for(int group=0;group<12;group++) {
  void *material=*(void **)(buckets+0x440+group*4);
  BkEffectGeometryBucketPS2 *bucket=(BkEffectGeometryBucketPS2 *)(buckets+group*0x88);
  int bound=0;
  if(!material)return;
  while(bucket) {
   for(int i=0;i<bucket->count;i++) {
    BkEffectGeometryPS2 *geometry=bucket->records[i];
    if(geometry->pass==pass) {
     if(!bound) {bound=1;func_001C45C0();func_001C4148(material);}
     if(geometry->vertexCount==4) {
      BkEffectDrawPacketPS2 packet;
      packet.points[0]=BkEffectTransformPS2(geometry->transform,geometry->points[0]);
      packet.points[1]=BkEffectTransformPS2(geometry->transform,geometry->points[1]);
      packet.points[2]=BkEffectTransformPS2(geometry->transform,geometry->points[3]);
      packet.points[3]=BkEffectTransformPS2(geometry->transform,geometry->points[2]);
      packet.normal=BkEffectRotatePS2(geometry->transform,geometry->normal);
      packet.uv[0]=geometry->uv[0];packet.uv[1]=geometry->uv[1];packet.uv[2]=geometry->uv[3];packet.uv[3]=geometry->uv[2];
      func_001C41D0(&packet);
     }else if(geometry->vertexCount==3) {
      BkEffectDrawPacketPS2 packet;
      for(int vertex=0;vertex<3;vertex++)packet.points[vertex]=BkEffectTransformPS2(geometry->transform,geometry->points[vertex]);
      packet.normal=BkEffectRotatePS2(geometry->transform,geometry->normal);
      packet.uv[0]=geometry->uv[0];packet.uv[1]=geometry->uv[1];packet.uv[2]=geometry->uv[2];func_001C43F0(&packet);
     }
    }
   }
   bucket=bucket->next;
  }
 }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B82E0);
#endif


#ifdef NON_MATCHING
#include "game/effects/pool.h"
#include "game/effects/vector.h"
static inline u32 PackColor(BkEffectPointPS2 color) {
 s128 v=*(s128 *)&color,packed,limit=(s128)0x8000ff00ff00ffULL;
 __asm__("vmulw.xyzw outv, cv, vf0w\n\tvftoi0.xyzw outv, outv":"=j outv"(v):"j cv"(v));
 __asm__("pextlh lv, zv, lv":"+r lv"(limit):"r zv"(0));
 __asm__("pminw pv, vv, lv\n\tppach pv, zv, pv\n\tppacb pv, zv, pv":"=r pv"(packed):"r vv"(v),"r lv"(limit),"r zv"(0));
 return (u32)packed;
}

extern void *D_0040F4C4;
extern "C" void *func_00108328(void *,const char *);
extern char D_003F7228[],D_003F7238[],D_003F7248[];
extern u32 D_00415A00[4];extern int D_00415A10;
// Unmatched: dynamic packed color initialization and vertex buffer lifetimes.
extern "C" int func_001BD638(char *effect) {
 int i;u32 *uv;
 if(!D_00415A10) {D_00415A10=1;D_00415A00[0]=0x3f666666;D_00415A00[1]=0;D_00415A00[2]=0;D_00415A00[3]=0x3e99999a;}
 *(void **)(effect+0x23f4)=func_00108328(D_0040F4C4,D_003F7228);
 *(void **)(effect+0x23f8)=func_00108328(D_0040F4C4,D_003F7238);
 *(void **)(effect+0x23fc)=func_00108328(D_0040F4C4,D_003F7248);
 for(i=0;i<18;i++) {effect[0x1200+i]=-1;*(u32 *)(effect+0x1214+i*4)=-1;}
 uv=(u32 *)(effect+0x1270);
 uv[0]=0;uv[1]=0;uv[8]=0;uv[9]=0x3f800000;uv[16]=0x3f800000;uv[17]=0x3f800000;
 uv[24]=0x3f800000;uv[25]=0;uv[32]=0;uv[33]=0;uv[40]=0;uv[41]=0x3f800000;
 uv[48]=0x3f800000;uv[49]=0x3f800000;uv[56]=0x3f800000;uv[57]=0;
 uv[64]=0;uv[65]=0;uv[72]=0;uv[73]=0x3f800000;uv[80]=0x3f800000;uv[81]=0x3f800000;
 uv[88]=0x3f800000;uv[89]=0;effect[0x13e0]=0;effect[0x13e1]=0;
 for(i=0;i<32;i++) {
  u32 *group=(u32 *)(effect+0x1400+i*0x80);
  for(int vertex=0;vertex<4;vertex++) {
   BkEffectPointPS2 color={((f32 *)D_00415A00)[0]*128.0f,((f32 *)D_00415A00)[1]*128.0f,((f32 *)D_00415A00)[2]*128.0f,((f32 *)D_00415A00)[3]*128.0f};
   group[vertex*8]=(vertex>=2)?0x3f800000:0;
   group[vertex*8+1]=(vertex==1||vertex==2)?0x3f800000:0;
   group[vertex*8+2]=PackColor(color);
  }
 }
 effect[0x23f0]=0;return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BD638);
#endif
