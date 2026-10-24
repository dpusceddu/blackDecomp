/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PERCEPTION_H
#define RECOVERED_PERCEPTION_H
#include "ps2/prelude.h"

typedef struct Recovered_Perception {
    u32 field_0; /* PS2 +0x0 */
    void * field_4; /* PS2 +0x4 */
    f32 field_8; /* PS2 +0x8 */
    f32 field_C; /* PS2 +0xC */
    u8 opaque_10[8];
    s32 field_18; /* PS2 +0x18 */
    s32 field_1C; /* PS2 +0x1C */
    s32 field_20; /* PS2 +0x20 */
    s32 field_24; /* PS2 +0x24 */
    s32 field_28; /* PS2 +0x28 */
    s32 field_2C; /* PS2 +0x2C */
    void * field_30; /* PS2 +0x30 */
    s32 field_34; /* PS2 +0x34 */
    void * field_38; /* PS2 +0x38 */
    void * field_3C; /* PS2 +0x3C */
    void * field_40; /* PS2 +0x40 */
    void * field_44; /* PS2 +0x44 */
    u8 field_48; /* PS2 +0x48 */
    u8 field_49; /* PS2 +0x49 */
    u8 opaque_4A[2];
    s32 field_4C; /* PS2 +0x4C */
    u8 opaque_50[4];
} Recovered_Perception;
typedef char assert_Recovered_Perception_0[(((int)&((Recovered_Perception *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Perception_4[(((int)&((Recovered_Perception *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_Perception_8[(((int)&((Recovered_Perception *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_Perception_C[(((int)&((Recovered_Perception *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_Perception_18[(((int)&((Recovered_Perception *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_Perception_1C[(((int)&((Recovered_Perception *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_Perception_20[(((int)&((Recovered_Perception *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_Perception_24[(((int)&((Recovered_Perception *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_Perception_28[(((int)&((Recovered_Perception *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_Perception_2C[(((int)&((Recovered_Perception *)0)->field_2C) == 44) ? 1 : -1];
typedef char assert_Recovered_Perception_30[(((int)&((Recovered_Perception *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_Perception_34[(((int)&((Recovered_Perception *)0)->field_34) == 52) ? 1 : -1];
typedef char assert_Recovered_Perception_38[(((int)&((Recovered_Perception *)0)->field_38) == 56) ? 1 : -1];
typedef char assert_Recovered_Perception_3C[(((int)&((Recovered_Perception *)0)->field_3C) == 60) ? 1 : -1];
typedef char assert_Recovered_Perception_40[(((int)&((Recovered_Perception *)0)->field_40) == 64) ? 1 : -1];
typedef char assert_Recovered_Perception_44[(((int)&((Recovered_Perception *)0)->field_44) == 68) ? 1 : -1];
typedef char assert_Recovered_Perception_48[(((int)&((Recovered_Perception *)0)->field_48) == 72) ? 1 : -1];
typedef char assert_Recovered_Perception_49[(((int)&((Recovered_Perception *)0)->field_49) == 73) ? 1 : -1];
typedef char assert_Recovered_Perception_4C[(((int)&((Recovered_Perception *)0)->field_4C) == 76) ? 1 : -1];
#endif
