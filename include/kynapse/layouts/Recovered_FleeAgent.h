/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_FLEEAGENT_H
#define RECOVERED_FLEEAGENT_H
#include "ps2/prelude.h"

typedef struct Recovered_FleeAgent {
    void * field_0; /* PS2 +0x0 */
    void * field_4; /* PS2 +0x4 */
    void * field_8; /* PS2 +0x8 */
    void * field_C; /* PS2 +0xC */
    s32 field_10; /* PS2 +0x10 */
    s32 field_14; /* PS2 +0x14 */
    u32 field_18; /* PS2 +0x18 */
    s32 field_1C; /* PS2 +0x1C */
    s32 field_20; /* PS2 +0x20 */
    s32 field_24; /* PS2 +0x24 */
    s32 field_28; /* PS2 +0x28 */
    s32 field_2C; /* PS2 +0x2C */
    s32 field_30; /* PS2 +0x30 */
    f32 field_34; /* PS2 +0x34 */
    f32 field_38; /* PS2 +0x38 */
    f32 field_3C; /* PS2 +0x3C */
    s32 field_40; /* PS2 +0x40 */
    s32 field_44; /* PS2 +0x44 */
    u8 field_48; /* PS2 +0x48 */
    u8 opaque_49[3];
    f32 field_4C; /* PS2 +0x4C */
    f32 field_50; /* PS2 +0x50 */
    f32 field_54; /* PS2 +0x54 */
    f32 field_58; /* PS2 +0x58 */
    void * field_5C; /* PS2 +0x5C */
    s32 field_60; /* PS2 +0x60 */
    u8 opaque_64[4];
    f32 field_68; /* PS2 +0x68 */
    s32 field_6C; /* PS2 +0x6C */
    u8 field_70; /* PS2 +0x70 */
    u8 field_71; /* PS2 +0x71 */
    u8 opaque_72[2];
    s32 field_74; /* PS2 +0x74 */
    u8 field_78; /* PS2 +0x78 */
    u8 opaque_79[3];
    s32 field_7C; /* PS2 +0x7C */
    s32 field_80; /* PS2 +0x80 */
    f32 field_84; /* PS2 +0x84 */
} Recovered_FleeAgent;
typedef char assert_Recovered_FleeAgent_0[(((int)&((Recovered_FleeAgent *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_4[(((int)&((Recovered_FleeAgent *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_8[(((int)&((Recovered_FleeAgent *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_C[(((int)&((Recovered_FleeAgent *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_10[(((int)&((Recovered_FleeAgent *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_14[(((int)&((Recovered_FleeAgent *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_18[(((int)&((Recovered_FleeAgent *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_1C[(((int)&((Recovered_FleeAgent *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_20[(((int)&((Recovered_FleeAgent *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_24[(((int)&((Recovered_FleeAgent *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_28[(((int)&((Recovered_FleeAgent *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_2C[(((int)&((Recovered_FleeAgent *)0)->field_2C) == 44) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_30[(((int)&((Recovered_FleeAgent *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_34[(((int)&((Recovered_FleeAgent *)0)->field_34) == 52) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_38[(((int)&((Recovered_FleeAgent *)0)->field_38) == 56) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_3C[(((int)&((Recovered_FleeAgent *)0)->field_3C) == 60) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_40[(((int)&((Recovered_FleeAgent *)0)->field_40) == 64) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_44[(((int)&((Recovered_FleeAgent *)0)->field_44) == 68) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_48[(((int)&((Recovered_FleeAgent *)0)->field_48) == 72) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_4C[(((int)&((Recovered_FleeAgent *)0)->field_4C) == 76) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_50[(((int)&((Recovered_FleeAgent *)0)->field_50) == 80) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_54[(((int)&((Recovered_FleeAgent *)0)->field_54) == 84) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_58[(((int)&((Recovered_FleeAgent *)0)->field_58) == 88) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_5C[(((int)&((Recovered_FleeAgent *)0)->field_5C) == 92) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_60[(((int)&((Recovered_FleeAgent *)0)->field_60) == 96) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_68[(((int)&((Recovered_FleeAgent *)0)->field_68) == 104) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_6C[(((int)&((Recovered_FleeAgent *)0)->field_6C) == 108) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_70[(((int)&((Recovered_FleeAgent *)0)->field_70) == 112) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_71[(((int)&((Recovered_FleeAgent *)0)->field_71) == 113) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_74[(((int)&((Recovered_FleeAgent *)0)->field_74) == 116) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_78[(((int)&((Recovered_FleeAgent *)0)->field_78) == 120) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_7C[(((int)&((Recovered_FleeAgent *)0)->field_7C) == 124) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_80[(((int)&((Recovered_FleeAgent *)0)->field_80) == 128) ? 1 : -1];
typedef char assert_Recovered_FleeAgent_84[(((int)&((Recovered_FleeAgent *)0)->field_84) == 132) ? 1 : -1];
#endif
