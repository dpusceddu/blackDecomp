#ifndef BLACK_ACTOR_VECTOR_MATH_H
#define BLACK_ACTOR_VECTOR_MATH_H
#include "ps2/prelude.h"
typedef s128 BkVectorPS2;
static inline BkVectorPS2 BkOnePS2(void) {
 BkVectorPS2 one; __asm__("vaddw.x onev, vf0, vf0w" : "=j onev"(one)); return one;
}
static inline BkVectorPS2 BkMultiplyPS2(BkVectorPS2 a,BkVectorPS2 b) {
 BkVectorPS2 result; __asm__("vmul.xyz resultv, av, bv" : "=j resultv"(result) : "j av"(a),"j bv"(b)); return result;
}
static inline float BkSumPS2(BkVectorPS2 v) {
 BkVectorPS2 one=BkOnePS2(),result; float value;
 __asm__("vadday.x ACC, vv, vvy\n\tvmaddz.x resultv, onev, vvz" : "=j resultv"(result):"j vv"(v),"j onev"(one));
 __asm__("qmfc2.ni valuev, resultv":"=r valuev"(value):"j resultv"(result));return value;
}
static inline BkVectorPS2 BkNormalizePS2(BkVectorPS2 v) {
 BkVectorPS2 square=BkMultiplyPS2(v,v),one=BkOnePS2(),sum,result,reciprocal;
 __asm__("vadday.x ACC, vv, vvy\n\tvmaddz.x sumv, onev, vvz" : "=j sumv"(sum):"j vv"(square),"j onev"(one));
 __asm__("vmove.xyzw resultv, vv\n\tvnop\n\tvnop\n\tvnop\n\tvrsqrt Q, vf0w, sumvx\n\tvaddw.x recipv, vf0, vf0w\n\tvwaitq\n\tvmulq.xyz resultv, resultv, Q\n\tvmulq.x recipv, recipv, Q":"=&j resultv"(result),"=j recipv"(reciprocal):"j vv"(v),"j sumv"(sum));return result;
}
static inline BkVectorPS2 BkCrossPS2(BkVectorPS2 a,BkVectorPS2 b) {
 BkVectorPS2 result;__asm__("vopmula.xyz ACC, av, bv\n\tvopmsub.xyz resultv, bv, av":"=j resultv"(result):"j av"(a),"j bv"(b));return result;
}
static inline float BkClampedDotPS2(BkVectorPS2 a,BkVectorPS2 b) {
 BkVectorPS2 v=BkMultiplyPS2(a,b),one=BkOnePS2(),negative,result;float value;
 __asm__("vsubw.x negv, vf0, vf0w":"=j negv"(negative));
 __asm__("vadday.x ACC, vv, vvy\n\tvmaddz.x resultv, onev, vvz\n\tvmax.x resultv, resultv, negv\n\tvminiw.x resultv, resultv, vf0w":"=j resultv"(result):"j vv"(v),"j onev"(one),"j negv"(negative));
 __asm__("qmfc2.ni valuev, resultv":"=r valuev"(value):"j resultv"(result));return value;
}
#endif
