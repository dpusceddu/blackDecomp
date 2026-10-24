/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PAIROWNER_H
#define RECOVERED_PAIROWNER_H
#include "ps2/prelude.h"

typedef struct Recovered_PairOwner {
    u32 field_0; /* PS2 +0x0 */
    u32 field_4; /* PS2 +0x4 */
    f32 field_8; /* PS2 +0x8 */
    f32 field_C; /* PS2 +0xC */
    u8 opaque_10[8];
    u32 field_18; /* PS2 +0x18 */
    u32 field_1C; /* PS2 +0x1C */
    u32 field_20; /* PS2 +0x20 */
    u32 field_24; /* PS2 +0x24 */
    u32 field_28; /* PS2 +0x28 */
    u32 field_2C; /* PS2 +0x2C */
    u32 field_30; /* PS2 +0x30 */
    u32 field_34; /* PS2 +0x34 */
    u32 field_38; /* PS2 +0x38 */
    u32 field_3C; /* PS2 +0x3C */
    u32 field_40; /* PS2 +0x40 */
    u32 field_44; /* PS2 +0x44 */
} Recovered_PairOwner;
typedef char assert_Recovered_PairOwner_0[(((int)&((Recovered_PairOwner *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_PairOwner_4[(((int)&((Recovered_PairOwner *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_PairOwner_8[(((int)&((Recovered_PairOwner *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_PairOwner_C[(((int)&((Recovered_PairOwner *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_PairOwner_18[(((int)&((Recovered_PairOwner *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_PairOwner_1C[(((int)&((Recovered_PairOwner *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_PairOwner_20[(((int)&((Recovered_PairOwner *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_PairOwner_24[(((int)&((Recovered_PairOwner *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_PairOwner_28[(((int)&((Recovered_PairOwner *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_PairOwner_2C[(((int)&((Recovered_PairOwner *)0)->field_2C) == 44) ? 1 : -1];
typedef char assert_Recovered_PairOwner_30[(((int)&((Recovered_PairOwner *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_PairOwner_34[(((int)&((Recovered_PairOwner *)0)->field_34) == 52) ? 1 : -1];
typedef char assert_Recovered_PairOwner_38[(((int)&((Recovered_PairOwner *)0)->field_38) == 56) ? 1 : -1];
typedef char assert_Recovered_PairOwner_3C[(((int)&((Recovered_PairOwner *)0)->field_3C) == 60) ? 1 : -1];
typedef char assert_Recovered_PairOwner_40[(((int)&((Recovered_PairOwner *)0)->field_40) == 64) ? 1 : -1];
typedef char assert_Recovered_PairOwner_44[(((int)&((Recovered_PairOwner *)0)->field_44) == 68) ? 1 : -1];
#endif
