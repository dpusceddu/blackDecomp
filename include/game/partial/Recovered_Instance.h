/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_INSTANCE_H
#define RECOVERED_INSTANCE_H
#include "ps2/prelude.h"

typedef struct Recovered_Instance {
    s32 field_0; /* PS2 +0x0 */
    void * field_4; /* PS2 +0x4 */
    u8 opaque_8[4];
    void * field_C; /* PS2 +0xC */
    s32 field_10; /* PS2 +0x10 */
    u8 opaque_14[16];
    f32 field_24; /* PS2 +0x24 */
    u8 opaque_28[8];
    u128 field_30; /* PS2 +0x30 */
    u128 field_40; /* PS2 +0x40 */
    s32 field_50; /* PS2 +0x50 */
    s32 field_54; /* PS2 +0x54 */
    s32 field_58; /* PS2 +0x58 */
    s16 field_5C; /* PS2 +0x5C */
    u8 opaque_5E[2];
    f32 field_60; /* PS2 +0x60 */
    f32 field_64; /* PS2 +0x64 */
    u8 opaque_68[8];
    s32 field_70; /* PS2 +0x70 */
    u8 opaque_74[340];
    s16 field_1C8; /* PS2 +0x1C8 */
    u8 opaque_1CA[1942];
    f32 field_960; /* PS2 +0x960 */
    f32 field_964; /* PS2 +0x964 */
    f32 field_968; /* PS2 +0x968 */
    u8 opaque_96C[4];
    s32 field_970; /* PS2 +0x970 */
    u8 opaque_974[12];
    u32 field_980; /* PS2 +0x980 */
    u8 opaque_984[8];
    s32 field_98C; /* PS2 +0x98C */
    u8 opaque_990[8];
    s32 field_998; /* PS2 +0x998 */
    s32 field_99C; /* PS2 +0x99C */
    f32 field_9A0; /* PS2 +0x9A0 */
    f32 field_9A4; /* PS2 +0x9A4 */
    u8 opaque_9A8[4];
    void * field_9AC; /* PS2 +0x9AC */
    u8 opaque_9B0[24];
    f32 field_9C8; /* PS2 +0x9C8 */
} Recovered_Instance;
typedef char assert_Recovered_Instance_0[(((int)&((Recovered_Instance *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Instance_4[(((int)&((Recovered_Instance *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_Instance_C[(((int)&((Recovered_Instance *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_Instance_10[(((int)&((Recovered_Instance *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_Instance_24[(((int)&((Recovered_Instance *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_Instance_30[(((int)&((Recovered_Instance *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_Instance_40[(((int)&((Recovered_Instance *)0)->field_40) == 64) ? 1 : -1];
typedef char assert_Recovered_Instance_50[(((int)&((Recovered_Instance *)0)->field_50) == 80) ? 1 : -1];
typedef char assert_Recovered_Instance_54[(((int)&((Recovered_Instance *)0)->field_54) == 84) ? 1 : -1];
typedef char assert_Recovered_Instance_58[(((int)&((Recovered_Instance *)0)->field_58) == 88) ? 1 : -1];
typedef char assert_Recovered_Instance_5C[(((int)&((Recovered_Instance *)0)->field_5C) == 92) ? 1 : -1];
typedef char assert_Recovered_Instance_60[(((int)&((Recovered_Instance *)0)->field_60) == 96) ? 1 : -1];
typedef char assert_Recovered_Instance_64[(((int)&((Recovered_Instance *)0)->field_64) == 100) ? 1 : -1];
typedef char assert_Recovered_Instance_70[(((int)&((Recovered_Instance *)0)->field_70) == 112) ? 1 : -1];
typedef char assert_Recovered_Instance_1C8[(((int)&((Recovered_Instance *)0)->field_1C8) == 456) ? 1 : -1];
typedef char assert_Recovered_Instance_960[(((int)&((Recovered_Instance *)0)->field_960) == 2400) ? 1 : -1];
typedef char assert_Recovered_Instance_964[(((int)&((Recovered_Instance *)0)->field_964) == 2404) ? 1 : -1];
typedef char assert_Recovered_Instance_968[(((int)&((Recovered_Instance *)0)->field_968) == 2408) ? 1 : -1];
typedef char assert_Recovered_Instance_970[(((int)&((Recovered_Instance *)0)->field_970) == 2416) ? 1 : -1];
typedef char assert_Recovered_Instance_980[(((int)&((Recovered_Instance *)0)->field_980) == 2432) ? 1 : -1];
typedef char assert_Recovered_Instance_98C[(((int)&((Recovered_Instance *)0)->field_98C) == 2444) ? 1 : -1];
typedef char assert_Recovered_Instance_998[(((int)&((Recovered_Instance *)0)->field_998) == 2456) ? 1 : -1];
typedef char assert_Recovered_Instance_99C[(((int)&((Recovered_Instance *)0)->field_99C) == 2460) ? 1 : -1];
typedef char assert_Recovered_Instance_9A0[(((int)&((Recovered_Instance *)0)->field_9A0) == 2464) ? 1 : -1];
typedef char assert_Recovered_Instance_9A4[(((int)&((Recovered_Instance *)0)->field_9A4) == 2468) ? 1 : -1];
typedef char assert_Recovered_Instance_9AC[(((int)&((Recovered_Instance *)0)->field_9AC) == 2476) ? 1 : -1];
typedef char assert_Recovered_Instance_9C8[(((int)&((Recovered_Instance *)0)->field_9C8) == 2504) ? 1 : -1];
#endif
