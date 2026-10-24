/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_NODECONNECTIVITY_H
#define RECOVERED_NODECONNECTIVITY_H
#include "ps2/prelude.h"

typedef struct Recovered_NodeConnectivity {
    u8 opaque_0[4];
    s32 field_4; /* PS2 +0x4 */
    void * field_8; /* PS2 +0x8 */
    u8 opaque_C[4];
    u64 field_10; /* PS2 +0x10 */
    u64 field_18; /* PS2 +0x18 */
    u64 field_20; /* PS2 +0x20 */
    u64 field_28; /* PS2 +0x28 */
    u64 field_30; /* PS2 +0x30 */
    u64 field_38; /* PS2 +0x38 */
    u64 field_40; /* PS2 +0x40 */
    u64 field_48; /* PS2 +0x48 */
    u64 field_50; /* PS2 +0x50 */
    u64 field_58; /* PS2 +0x58 */
    u64 field_60; /* PS2 +0x60 */
    u64 field_68; /* PS2 +0x68 */
    u64 field_70; /* PS2 +0x70 */
    u64 field_78; /* PS2 +0x78 */
    u64 field_80; /* PS2 +0x80 */
    u64 field_88; /* PS2 +0x88 */
    u64 field_90; /* PS2 +0x90 */
    u64 field_98; /* PS2 +0x98 */
    u64 field_A0; /* PS2 +0xA0 */
    u64 field_A8; /* PS2 +0xA8 */
    u64 field_B0; /* PS2 +0xB0 */
    u64 field_B8; /* PS2 +0xB8 */
    u64 field_C0; /* PS2 +0xC0 */
    u64 field_C8; /* PS2 +0xC8 */
    u64 field_D0; /* PS2 +0xD0 */
    u64 field_D8; /* PS2 +0xD8 */
    u64 field_E0; /* PS2 +0xE0 */
    u64 field_E8; /* PS2 +0xE8 */
    u64 field_F0; /* PS2 +0xF0 */
    u64 field_F8; /* PS2 +0xF8 */
    u64 field_100; /* PS2 +0x100 */
    u64 field_108; /* PS2 +0x108 */
} Recovered_NodeConnectivity;
typedef char assert_Recovered_NodeConnectivity_4[(((int)&((Recovered_NodeConnectivity *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_8[(((int)&((Recovered_NodeConnectivity *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_10[(((int)&((Recovered_NodeConnectivity *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_18[(((int)&((Recovered_NodeConnectivity *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_20[(((int)&((Recovered_NodeConnectivity *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_28[(((int)&((Recovered_NodeConnectivity *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_30[(((int)&((Recovered_NodeConnectivity *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_38[(((int)&((Recovered_NodeConnectivity *)0)->field_38) == 56) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_40[(((int)&((Recovered_NodeConnectivity *)0)->field_40) == 64) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_48[(((int)&((Recovered_NodeConnectivity *)0)->field_48) == 72) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_50[(((int)&((Recovered_NodeConnectivity *)0)->field_50) == 80) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_58[(((int)&((Recovered_NodeConnectivity *)0)->field_58) == 88) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_60[(((int)&((Recovered_NodeConnectivity *)0)->field_60) == 96) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_68[(((int)&((Recovered_NodeConnectivity *)0)->field_68) == 104) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_70[(((int)&((Recovered_NodeConnectivity *)0)->field_70) == 112) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_78[(((int)&((Recovered_NodeConnectivity *)0)->field_78) == 120) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_80[(((int)&((Recovered_NodeConnectivity *)0)->field_80) == 128) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_88[(((int)&((Recovered_NodeConnectivity *)0)->field_88) == 136) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_90[(((int)&((Recovered_NodeConnectivity *)0)->field_90) == 144) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_98[(((int)&((Recovered_NodeConnectivity *)0)->field_98) == 152) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_A0[(((int)&((Recovered_NodeConnectivity *)0)->field_A0) == 160) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_A8[(((int)&((Recovered_NodeConnectivity *)0)->field_A8) == 168) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_B0[(((int)&((Recovered_NodeConnectivity *)0)->field_B0) == 176) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_B8[(((int)&((Recovered_NodeConnectivity *)0)->field_B8) == 184) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_C0[(((int)&((Recovered_NodeConnectivity *)0)->field_C0) == 192) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_C8[(((int)&((Recovered_NodeConnectivity *)0)->field_C8) == 200) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_D0[(((int)&((Recovered_NodeConnectivity *)0)->field_D0) == 208) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_D8[(((int)&((Recovered_NodeConnectivity *)0)->field_D8) == 216) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_E0[(((int)&((Recovered_NodeConnectivity *)0)->field_E0) == 224) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_E8[(((int)&((Recovered_NodeConnectivity *)0)->field_E8) == 232) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_F0[(((int)&((Recovered_NodeConnectivity *)0)->field_F0) == 240) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_F8[(((int)&((Recovered_NodeConnectivity *)0)->field_F8) == 248) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_100[(((int)&((Recovered_NodeConnectivity *)0)->field_100) == 256) ? 1 : -1];
typedef char assert_Recovered_NodeConnectivity_108[(((int)&((Recovered_NodeConnectivity *)0)->field_108) == 264) ? 1 : -1];
#endif
