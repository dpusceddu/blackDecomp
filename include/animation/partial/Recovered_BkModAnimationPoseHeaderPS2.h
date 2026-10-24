/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_BKMODANIMATIONPOSEHEADERPS2_H
#define RECOVERED_BKMODANIMATIONPOSEHEADERPS2_H
#include "ps2/prelude.h"

typedef struct Recovered_BkModAnimationPoseHeaderPS2 {
    u128 field_0; /* PS2 +0x0 */
    u128 field_10; /* PS2 +0x10 */
} Recovered_BkModAnimationPoseHeaderPS2;
typedef char assert_Recovered_BkModAnimationPoseHeaderPS2_0[(((int)&((Recovered_BkModAnimationPoseHeaderPS2 *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_BkModAnimationPoseHeaderPS2_10[(((int)&((Recovered_BkModAnimationPoseHeaderPS2 *)0)->field_10) == 16) ? 1 : -1];
#endif
