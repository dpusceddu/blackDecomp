// Unmatched: VU normalization and random-state scheduling.
#ifdef NONMATCHING
#include "game/effects/random.h"
#include "game/actor/vector_math.h"
extern "C" s128 func_001BC880(void) {
 union {f32 f;u32 u;} x,y,z;
 s128 a,b,vector,result,square,sum,one=BkOnePS2();
 x.f=BkEffectRandomPS2()+0.01f;y.f=BkEffectRandomPS2();z.f=BkEffectRandomPS2();
 __asm__("pextlw outv, zv, xv":"=r outv"(a):"r zv"(z.u),"r xv"(x.u));
 __asm__("pextlw outv, yv, av":"=r outv"(b):"r yv"(y.u),"r av"(a));
 vector=b;
 square=BkMultiplyPS2(vector,vector);
 __asm__("vadday.x ACC, vv, vvy\n\tvmaddz.x sumv, onev, vvz":"=j sumv"(sum):"j vv"(square),"j onev"(one));
 __asm__("vnop\n\tvnop\n\tvnop\n\tvrsqrt Q, vf0w, sumvx\n\tvwaitq\n\tvmulq.xyz outv, vv, Q":"=j outv"(vector):"j vv"(vector),"j sumv"(sum));
 __asm__("qmfc2.ni outv, vv":"=r outv"(result):"j vv"(vector));return result;
}

#endif // NONMATCHING
