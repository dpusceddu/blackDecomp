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
#ifdef NONMATCHING
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
#endif // NONMATCHING
