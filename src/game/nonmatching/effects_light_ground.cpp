#include "game/effects/vector.h"
extern "C" {extern char *D_0040F4D0;extern s128 D_00415A70,D_00415A90;extern int D_00415A80,D_00415AA0;void func_001B1038(...);int func_0012AE58(void *,s128,s128,int,int,int,void *);}
static inline s128 Add(s128 a,s128 b) {s128 r;__asm__("vadd.xyz outv, av, bv":"=j outv"(r):"j av"(a),"j bv"(b));return r;}
static inline s128 Half(s128 a) {s128 r,s;__asm__("qmtc2.ni fr, sv":"=j sv"(s):"r fr"(0.5f));__asm__("vmulx.xyz outv, av, svx":"=j outv"(r):"j av"(a),"j sv"(s));return r;}
// Unmatched: ground-ray hit aggregate, vector argument bank and static vector initialization.
#ifdef NONMATCHING
extern "C" int func_001C0910(char *light,void *owner,void *resource,void *context,const s128 *transform) {
 BkEffectPointPS2 up={0,0.2f,0,0},down={0,-100,0,0},hit[4];
 if(!D_00415A80) {D_00415A70=*(s128 *)&up;D_00415A80=1;}
 if(!D_00415AA0) {D_00415A90=*(s128 *)&down;D_00415AA0=1;}
 func_001B1038(light,owner,resource);*(u32 *)(light+0x54)=0;
 s128 half=Half(transform[2]),bottom=Add(Add(transform[3],D_00415A90),half),top=Add(Add(transform[3],D_00415A70),half);
 if(func_0012AE58(D_0040F4D0,top,bottom,1,0,1,hit))*(f32 *)(light+0x58)=hit[0].y;
 else *(f32 *)(light+0x58)=BkEffectSpillPS2(transform[3]).y-3.0f;
 *(void **)(light+0x50)=context;return 1;
}
#endif // NONMATCHING
