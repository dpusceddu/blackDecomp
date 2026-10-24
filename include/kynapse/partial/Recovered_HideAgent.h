/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_HIDEAGENT_H
#define RECOVERED_HIDEAGENT_H
#include "ps2/prelude.h"

typedef struct Recovered_HideAgent {
    void * field_0; /* PS2 +0x0 */
    void * field_4; /* PS2 +0x4 */
    void * field_8; /* PS2 +0x8 */
    s32 field_C; /* PS2 +0xC */
    void * field_10; /* PS2 +0x10 */
    f32 field_14; /* PS2 +0x14 */
    f32 field_18; /* PS2 +0x18 */
    f32 field_1C; /* PS2 +0x1C */
    s32 field_20; /* PS2 +0x20 */
    s32 field_24; /* PS2 +0x24 */
    s32 field_28; /* PS2 +0x28 */
    u8 opaque_2C[4];
    s32 field_30; /* PS2 +0x30 */
    u8 field_34; /* PS2 +0x34 */
    u8 field_35; /* PS2 +0x35 */
    u8 opaque_36[2];
    void * field_38; /* PS2 +0x38 */
    s8 field_3C; /* PS2 +0x3C */
    u8 opaque_3D[3];
    s32 field_40; /* PS2 +0x40 */
    s32 field_44; /* PS2 +0x44 */
    s32 field_48; /* PS2 +0x48 */
    s32 field_4C; /* PS2 +0x4C */
    void * field_50; /* PS2 +0x50 */
    u8 opaque_54[4];
    s32 field_58; /* PS2 +0x58 */
    u8 opaque_5C[4];
    f32 field_60; /* PS2 +0x60 */
    f32 field_64; /* PS2 +0x64 */
    u8 field_68; /* PS2 +0x68 */
    u8 opaque_69[3];
    u32 field_6C; /* PS2 +0x6C */
    s32 field_70; /* PS2 +0x70 */
    void * field_74; /* PS2 +0x74 */
    f32 field_78; /* PS2 +0x78 */
    s32 field_7C; /* PS2 +0x7C */
} Recovered_HideAgent;
typedef char assert_Recovered_HideAgent_0[(((int)&((Recovered_HideAgent *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_HideAgent_4[(((int)&((Recovered_HideAgent *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_HideAgent_8[(((int)&((Recovered_HideAgent *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_HideAgent_C[(((int)&((Recovered_HideAgent *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_HideAgent_10[(((int)&((Recovered_HideAgent *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_HideAgent_14[(((int)&((Recovered_HideAgent *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_HideAgent_18[(((int)&((Recovered_HideAgent *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_HideAgent_1C[(((int)&((Recovered_HideAgent *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_HideAgent_20[(((int)&((Recovered_HideAgent *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_HideAgent_24[(((int)&((Recovered_HideAgent *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_HideAgent_28[(((int)&((Recovered_HideAgent *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_HideAgent_30[(((int)&((Recovered_HideAgent *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_HideAgent_34[(((int)&((Recovered_HideAgent *)0)->field_34) == 52) ? 1 : -1];
typedef char assert_Recovered_HideAgent_35[(((int)&((Recovered_HideAgent *)0)->field_35) == 53) ? 1 : -1];
typedef char assert_Recovered_HideAgent_38[(((int)&((Recovered_HideAgent *)0)->field_38) == 56) ? 1 : -1];
typedef char assert_Recovered_HideAgent_3C[(((int)&((Recovered_HideAgent *)0)->field_3C) == 60) ? 1 : -1];
typedef char assert_Recovered_HideAgent_40[(((int)&((Recovered_HideAgent *)0)->field_40) == 64) ? 1 : -1];
typedef char assert_Recovered_HideAgent_44[(((int)&((Recovered_HideAgent *)0)->field_44) == 68) ? 1 : -1];
typedef char assert_Recovered_HideAgent_48[(((int)&((Recovered_HideAgent *)0)->field_48) == 72) ? 1 : -1];
typedef char assert_Recovered_HideAgent_4C[(((int)&((Recovered_HideAgent *)0)->field_4C) == 76) ? 1 : -1];
typedef char assert_Recovered_HideAgent_50[(((int)&((Recovered_HideAgent *)0)->field_50) == 80) ? 1 : -1];
typedef char assert_Recovered_HideAgent_58[(((int)&((Recovered_HideAgent *)0)->field_58) == 88) ? 1 : -1];
typedef char assert_Recovered_HideAgent_60[(((int)&((Recovered_HideAgent *)0)->field_60) == 96) ? 1 : -1];
typedef char assert_Recovered_HideAgent_64[(((int)&((Recovered_HideAgent *)0)->field_64) == 100) ? 1 : -1];
typedef char assert_Recovered_HideAgent_68[(((int)&((Recovered_HideAgent *)0)->field_68) == 104) ? 1 : -1];
typedef char assert_Recovered_HideAgent_6C[(((int)&((Recovered_HideAgent *)0)->field_6C) == 108) ? 1 : -1];
typedef char assert_Recovered_HideAgent_70[(((int)&((Recovered_HideAgent *)0)->field_70) == 112) ? 1 : -1];
typedef char assert_Recovered_HideAgent_74[(((int)&((Recovered_HideAgent *)0)->field_74) == 116) ? 1 : -1];
typedef char assert_Recovered_HideAgent_78[(((int)&((Recovered_HideAgent *)0)->field_78) == 120) ? 1 : -1];
typedef char assert_Recovered_HideAgent_7C[(((int)&((Recovered_HideAgent *)0)->field_7C) == 124) ? 1 : -1];
#endif
