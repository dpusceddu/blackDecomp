#include "ps2/vu0_math.h"

/* Isolated compiler controls. Their arithmetic windows are compared with retail;
   these are not substitutes for full-function/full-image verification. */
extern "C" {
BkVuVector VuMath_Add(BkVuVector a,BkVuVector b) { return BkVuAddXYZ(a,b); }
BkVuVector VuMath_Sub(BkVuVector a,BkVuVector b) { return BkVuSubXYZ(a,b); }
BkVuVector VuMath_Mul(BkVuVector a,BkVuVector b) { return BkVuMulXYZ(a,b); }
BkVuVector VuMath_One() { return BkVuOneX(); }
BkVuVector VuMath_Sum(BkVuVector a,BkVuVector one) { return BkVuSumXYZ(a,one); }
BkVuVector VuMath_Sqrt(BkVuVector sum) { return BkVuSqrtX(sum); }
BkVuVector VuMath_Scale(BkVuVector a,BkVuVector scale) { return BkVuScaleXYZ(a,scale); }
BkVuVector VuMath_Cross(BkVuVector a,BkVuVector b) { return BkVuCrossXYZ(a,b); }
BkVuVector VuMath_Normalize(BkVuVector a,BkVuVector sum) { return BkVuNormalizeXYZ(a,sum); }
BkVuVector VuMath_NormalizeW(BkVuVector a,BkVuVector sum) { return BkVuNormalizeXYZPreserveW(a,sum); }
}
