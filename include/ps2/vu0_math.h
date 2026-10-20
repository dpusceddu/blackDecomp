#ifndef BLACK_PS2_VU0_MATH_H
#define BLACK_PS2_VU0_MATH_H
#include "ps2/ee_types.h"

/* C-compatible VU0 macro operations. SN's j operands allocate vector registers;
   callers use -mvu0-use-vf0-vf31. XYZ outputs leave W unspecified unless named
   PreserveW. ACC and Q operations are indivisible asm blocks: their hidden
   state is consumed inside the same block. No API exports MAC/status flags. */
typedef EeS128 BkVuVector;
static inline BkVuVector BkVuAddXYZ(BkVuVector a, BkVuVector b)
{
 BkVuVector r; __asm__("vadd.xyz outv, av, bv":"=j outv"(r):"j av"(a),"j bv"(b)); return r;
}
static inline BkVuVector BkVuSubXYZ(BkVuVector a, BkVuVector b)
{
 BkVuVector r; __asm__("vsub.xyz outv, av, bv":"=j outv"(r):"j av"(a),"j bv"(b)); return r;
}
static inline BkVuVector BkVuMulXYZ(BkVuVector a, BkVuVector b)
{
 BkVuVector r; __asm__("vmul.xyz outv, av, bv":"=j outv"(r):"j av"(a),"j bv"(b)); return r;
}
static inline BkVuVector BkVuScaleXYZ(BkVuVector a, BkVuVector scalar)
{
 BkVuVector r; __asm__("vmulx.xyz outv, av, scalarvx":"=j outv"(r):"j av"(a),"j scalarv"(scalar)); return r;
}
static inline BkVuVector BkVuOneX(void)
{
 BkVuVector r; __asm__("vaddw.x outv, vf0, vf0w":"=j outv"(r)); return r;
}
static inline BkVuVector BkVuSumXYZ(BkVuVector v, BkVuVector one)
{
 BkVuVector r; __asm__("vadday.x ACC, vv, vvy\n\tvmaddz.x outv, onev, vvz":"=j outv"(r):"j vv"(v),"j onev"(one)); return r;
}
static inline BkVuVector BkVuCrossXYZ(BkVuVector a, BkVuVector b)
{
 BkVuVector r; __asm__("vopmula.xyz ACC, av, bv\n\tvopmsub.xyz outv, bv, av":"=j outv"(r):"j av"(a),"j bv"(b)); return r;
}
/* Short normalization shape: no zero guard, W unspecified. The three vnops and
   vwaitq are part of the retail scheduling recipe, not inserted output padding. */
static inline BkVuVector BkVuNormalizeXYZ(BkVuVector v, BkVuVector sum)
{
 BkVuVector r; __asm__("vnop\n\tvnop\n\tvnop\n\tvrsqrt Q, vf0w, sumvx\n\tvwaitq\n\tvmulq.xyz outv, vv, Q":"=j outv"(r):"j vv"(v),"j sumv"(sum)); return r;
}
static inline BkVuVector BkVuNormalizeXYZPreserveW(BkVuVector v, BkVuVector sum)
{
 BkVuVector r; __asm__("vmove.xyzw outv, vv\n\tvnop\n\tvnop\n\tvnop\n\tvrsqrt Q, vf0w, sumvx\n\tvwaitq\n\tvmulq.xyz outv, outv, Q":"=&j outv"(r):"j vv"(v),"j sumv"(sum)); return r;
}
static inline BkVuVector BkVuSqrtX(BkVuVector sum)
{
 BkVuVector r; __asm__("vnop\n\tvnop\n\tvnop\n\tvsqrt Q, sumvx\n\tvaddw.x outv, vf0, vf0w\n\tvwaitq\n\tvmulq.x outv, outv, Q":"=j outv"(r):"j sumv"(sum)); return r;
}
#endif
