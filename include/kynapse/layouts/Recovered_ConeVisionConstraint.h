/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_CONEVISIONCONSTRAINT_H
#define RECOVERED_CONEVISIONCONSTRAINT_H
#include "ps2/prelude.h"

typedef struct Recovered_ConeVisionConstraint {
    u8 opaque_0[4];
    void * field_4; /* PS2 +0x4 */
    void * field_8; /* PS2 +0x8 */
    void * field_C; /* PS2 +0xC */
    void * field_10; /* PS2 +0x10 */
    void * field_14; /* PS2 +0x14 */
    void * field_18; /* PS2 +0x18 */
    void * field_1C; /* PS2 +0x1C */
    void * field_20; /* PS2 +0x20 */
    u8 opaque_24[48];
    s32 field_54; /* PS2 +0x54 */
    f32 field_58; /* PS2 +0x58 */
    f32 field_5C; /* PS2 +0x5C */
} Recovered_ConeVisionConstraint;
typedef char assert_Recovered_ConeVisionConstraint_4[(((int)&((Recovered_ConeVisionConstraint *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_ConeVisionConstraint_8[(((int)&((Recovered_ConeVisionConstraint *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_ConeVisionConstraint_C[(((int)&((Recovered_ConeVisionConstraint *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_ConeVisionConstraint_10[(((int)&((Recovered_ConeVisionConstraint *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_ConeVisionConstraint_14[(((int)&((Recovered_ConeVisionConstraint *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_ConeVisionConstraint_18[(((int)&((Recovered_ConeVisionConstraint *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_ConeVisionConstraint_1C[(((int)&((Recovered_ConeVisionConstraint *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_ConeVisionConstraint_20[(((int)&((Recovered_ConeVisionConstraint *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_ConeVisionConstraint_54[(((int)&((Recovered_ConeVisionConstraint *)0)->field_54) == 84) ? 1 : -1];
typedef char assert_Recovered_ConeVisionConstraint_58[(((int)&((Recovered_ConeVisionConstraint *)0)->field_58) == 88) ? 1 : -1];
typedef char assert_Recovered_ConeVisionConstraint_5C[(((int)&((Recovered_ConeVisionConstraint *)0)->field_5C) == 92) ? 1 : -1];
#endif
