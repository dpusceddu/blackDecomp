#ifndef BLACK_PS2_VU0_LOWERING_H
#define BLACK_PS2_VU0_LOWERING_H
#include "ps2/vu0_math.h"

/* Private decompiler spellings keep generated extern declarations out of the
   source context; every expansion below is a normal shared inline operation. */
#define __ee_vu_add BkVuAddXYZ
#define __ee_vu_sub BkVuSubXYZ
#define __ee_vu_mul BkVuMulXYZ
#define __ee_vu_one BkVuOneX
#define __ee_vu_sum BkVuSumXYZ
#define __ee_vu_cross BkVuCrossXYZ
#define __ee_vu_normalize BkVuNormalizeXYZ
#define __ee_vu_sqrt BkVuSqrtX
#define __ee_vu_add_keep BkVuLowerAddXYZ
#define __ee_vu_sub_keep BkVuLowerSubXYZ
#define __ee_vu_mul_keep BkVuLowerMulXYZ
#define __ee_vu_one_keep BkVuLowerOneX
#define __ee_vu_sum_keep BkVuLowerSumXYZ
#define __ee_vu_cross_keep BkVuLowerCrossXYZ
#define __ee_vu_normalize_keep BkVuLowerNormalizeXYZ
#define __ee_vu_sqrt_keep BkVuLowerSqrtX

/* Semantic adapters for the opt-in m2c path. Partial results retain the old
   destination lanes explicitly. These are operations, not register replay. */
#define BK_VU_LOWER_BINARY(name, instruction) \
static inline BkVuVector name(BkVuVector old, BkVuVector a, BkVuVector b) \
{ __asm__(instruction " outv, av, bv":"+j outv"(old):"j av"(a),"j bv"(b)); return old; }
BK_VU_LOWER_BINARY(BkVuLowerAddXYZ, "vadd.xyz")
BK_VU_LOWER_BINARY(BkVuLowerSubXYZ, "vsub.xyz")
BK_VU_LOWER_BINARY(BkVuLowerMulXYZ, "vmul.xyz")
#undef BK_VU_LOWER_BINARY
static inline BkVuVector BkVuLowerOneX(BkVuVector old)
{ __asm__("vaddw.x outv, vf0, vf0w":"+j outv"(old)); return old; }
static inline BkVuVector BkVuLowerSumXYZ(BkVuVector old, BkVuVector v, BkVuVector one)
{ __asm__("vadday.x ACC, vv, vvy\n\tvmaddz.x outv, onev, vvz":"+j outv"(old):"j vv"(v),"j onev"(one)); return old; }
static inline BkVuVector BkVuLowerCrossXYZ(BkVuVector old, BkVuVector a, BkVuVector b)
{ __asm__("vopmula.xyz ACC, av, bv\n\tvopmsub.xyz outv, bv, av":"+j outv"(old):"j av"(a),"j bv"(b)); return old; }
static inline BkVuVector BkVuLowerNormalizeXYZ(BkVuVector old, BkVuVector v, BkVuVector sum)
{ __asm__("vnop\n\tvnop\n\tvnop\n\tvrsqrt Q, vf0w, sumvx\n\tvwaitq\n\tvmulq.xyz outv, vv, Q":"+j outv"(old):"j vv"(v),"j sumv"(sum)); return old; }
static inline BkVuVector BkVuLowerSqrtX(BkVuVector old, BkVuVector sum)
{ __asm__("vnop\n\tvnop\n\tvnop\n\tvsqrt Q, sumvx\n\tvaddw.x outv, vf0, vf0w\n\tvwaitq\n\tvmulq.x outv, outv, Q":"+j outv"(old):"j sumv"(sum)); return old; }
#endif
