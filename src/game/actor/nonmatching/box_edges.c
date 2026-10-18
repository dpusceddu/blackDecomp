// Unmatched: 0x1ae5e8: VU0 corner construction, packed color, and vertex stack layout.
#ifdef NONMATCHING
#include "game/actor/vector_math.h"
typedef struct {BkVectorPS2 position;int a,b;unsigned int color;int c;} BkLineVertexPS2;
extern void func_0026B480(void *,BkLineVertexPS2 *,int);
static inline float lane(BkVectorPS2 value,int index){float p[4] __attribute__((aligned(16)));__asm__("sqc2 vv, 0(pv)"::"j vv"(value),"r pv"(p):"memory");return p[index];}
static inline BkVectorPS2 make(float x,float y,float z){BkVectorPS2 tmp,result;__asm__("pextlw tv, zv, xv":"=r tv"(tmp):"r zv"(z),"r xv"(x));__asm__("pextlw rv, yv, tv":"=r rv"(result):"r yv"(y),"r tv"(tmp));return result;}
static inline unsigned int color32(BkVectorPS2 color){BkVectorPS2 converted,limit,clamped,shorts,packed;float scale=128.0f;int scaleBits=0x43000000;s64 limits=0x8000;
 limits=(limits<<16)|0xff00;limits=(limits<<16)|0xff00;limits=(limits<<8)|0xff;
 __asm__("pextlh lv, $0, cv":"=r lv"(limit):"r cv"(limits));
 __asm__("vmulx.xyzw rv, cv, svx\n\tvftoi0.xyzw iv, rv":"=j rv"(clamped),"=j iv"(converted):"j cv"(color),"j sv"((BkVectorPS2)scaleBits));
 __asm__("pminw rv, cv, lv\n\tppach shv, $0, rv\n\tppacb pv, $0, shv":"=r rv"(clamped),"=r shv"(shorts),"=r pv"(packed):"r cv"(converted),"r lv"(limit));return (unsigned int)packed;}
void func_001AE5E8(void *unused,void *renderer,BkVectorPS2 low,BkVectorPS2 high,BkVectorPS2 color){
 static const int edges[24]={0,1,1,2,2,3,3,0,0,4,1,5,2,6,3,7,4,5,5,6,6,7,7,4};
 BkVectorPS2 corner[8];BkLineVertexPS2 vertices[24];unsigned int packed;int i;float x0=lane(low,0),x1=lane(high,0);
 corner[0]=make(x0,lane(low,1),lane(low,2));corner[1]=make(x1,lane(low,1),lane(low,2));
 corner[2]=make(x1,lane(low,1),lane(high,2));corner[3]=make(x0,lane(low,1),lane(high,2));
 corner[4]=make(x0,lane(high,1),lane(low,2));corner[5]=make(x1,lane(high,1),lane(low,2));
 corner[6]=make(x1,lane(high,1),lane(high,2));corner[7]=make(x0,lane(high,1),lane(high,2));
 packed=color32(color);
 for(i=0;i<24;i++) {BkVectorPS2 v=corner[edges[i]],r;__asm__("vadd.xyz rv, vf0, vv":"=j rv"(r):"j vv"(v));vertices[i].position=r;vertices[i].color=packed;}
 func_0026B480(renderer,vertices,24);
}

#endif
