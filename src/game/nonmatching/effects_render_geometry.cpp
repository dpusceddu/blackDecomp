#include "game/effects/geometry.h"
struct BkEffectDrawPacketPS2 { BkEffectVectorPS2 normal,points[4];BkEffectUVPS2 uv[4]; };
extern "C" void func_001C45C0(void),func_001C4148(void *),func_001C41D0(void *),func_001C43F0(void *);
// Unmatched: matrix temporary lifetimes and original empty vector-constructor loops.
#ifdef NONMATCHING
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
#endif // NONMATCHING
