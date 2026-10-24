/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PHYSICSSCENE_H
#define RECOVERED_PHYSICSSCENE_H
#include "ps2/prelude.h"

typedef struct Recovered_PhysicsScene {
    u8 opaque_0[4];
    s32 field_4; /* PS2 +0x4 */
    s32 field_8; /* PS2 +0x8 */
    s32 field_C; /* PS2 +0xC */
    void * field_10; /* PS2 +0x10 */
    u8 opaque_14[4];
    void * field_18; /* PS2 +0x18 */
    void * field_1C; /* PS2 +0x1C */
    s32 field_20; /* PS2 +0x20 */
    s32 field_24; /* PS2 +0x24 */
    s32 field_28; /* PS2 +0x28 */
    s32 field_2C; /* PS2 +0x2C */
    s32 field_30; /* PS2 +0x30 */
    s32 field_34; /* PS2 +0x34 */
    s32 field_38; /* PS2 +0x38 */
    s32 field_3C; /* PS2 +0x3C */
    void * field_40; /* PS2 +0x40 */
    s32 field_44; /* PS2 +0x44 */
    s32 field_48; /* PS2 +0x48 */
    s32 field_4C; /* PS2 +0x4C */
    s32 field_50; /* PS2 +0x50 */
    s32 field_54; /* PS2 +0x54 */
    s32 field_58; /* PS2 +0x58 */
    s32 field_5C; /* PS2 +0x5C */
    void * field_60; /* PS2 +0x60 */
    u8 opaque_64[4];
    s32 field_68; /* PS2 +0x68 */
    s32 field_6C; /* PS2 +0x6C */
    u8 opaque_70[8];
    void * field_78; /* PS2 +0x78 */
    s32 field_7C; /* PS2 +0x7C */
    s32 field_80; /* PS2 +0x80 */
    void * field_84; /* PS2 +0x84 */
    u8 opaque_88[4];
    s32 field_8C; /* PS2 +0x8C */
    s32 field_90; /* PS2 +0x90 */
    u8 opaque_94[8];
    s32 field_9C; /* PS2 +0x9C */
    u8 opaque_A0[8];
    void * field_A8; /* PS2 +0xA8 */
    s32 field_AC; /* PS2 +0xAC */
    s32 field_B0; /* PS2 +0xB0 */
    void * field_B4; /* PS2 +0xB4 */
    s32 field_B8; /* PS2 +0xB8 */
    s32 field_BC; /* PS2 +0xBC */
    void * field_C0; /* PS2 +0xC0 */
    u8 opaque_C4[4];
    s32 field_C8; /* PS2 +0xC8 */
    void * field_CC; /* PS2 +0xCC */
    u8 opaque_D0[4];
    s32 field_D4; /* PS2 +0xD4 */
    void * field_D8; /* PS2 +0xD8 */
} Recovered_PhysicsScene;
typedef char assert_Recovered_PhysicsScene_4[(((int)&((Recovered_PhysicsScene *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_8[(((int)&((Recovered_PhysicsScene *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_C[(((int)&((Recovered_PhysicsScene *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_10[(((int)&((Recovered_PhysicsScene *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_18[(((int)&((Recovered_PhysicsScene *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_1C[(((int)&((Recovered_PhysicsScene *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_20[(((int)&((Recovered_PhysicsScene *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_24[(((int)&((Recovered_PhysicsScene *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_28[(((int)&((Recovered_PhysicsScene *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_2C[(((int)&((Recovered_PhysicsScene *)0)->field_2C) == 44) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_30[(((int)&((Recovered_PhysicsScene *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_34[(((int)&((Recovered_PhysicsScene *)0)->field_34) == 52) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_38[(((int)&((Recovered_PhysicsScene *)0)->field_38) == 56) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_3C[(((int)&((Recovered_PhysicsScene *)0)->field_3C) == 60) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_40[(((int)&((Recovered_PhysicsScene *)0)->field_40) == 64) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_44[(((int)&((Recovered_PhysicsScene *)0)->field_44) == 68) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_48[(((int)&((Recovered_PhysicsScene *)0)->field_48) == 72) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_4C[(((int)&((Recovered_PhysicsScene *)0)->field_4C) == 76) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_50[(((int)&((Recovered_PhysicsScene *)0)->field_50) == 80) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_54[(((int)&((Recovered_PhysicsScene *)0)->field_54) == 84) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_58[(((int)&((Recovered_PhysicsScene *)0)->field_58) == 88) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_5C[(((int)&((Recovered_PhysicsScene *)0)->field_5C) == 92) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_60[(((int)&((Recovered_PhysicsScene *)0)->field_60) == 96) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_68[(((int)&((Recovered_PhysicsScene *)0)->field_68) == 104) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_6C[(((int)&((Recovered_PhysicsScene *)0)->field_6C) == 108) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_78[(((int)&((Recovered_PhysicsScene *)0)->field_78) == 120) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_7C[(((int)&((Recovered_PhysicsScene *)0)->field_7C) == 124) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_80[(((int)&((Recovered_PhysicsScene *)0)->field_80) == 128) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_84[(((int)&((Recovered_PhysicsScene *)0)->field_84) == 132) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_8C[(((int)&((Recovered_PhysicsScene *)0)->field_8C) == 140) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_90[(((int)&((Recovered_PhysicsScene *)0)->field_90) == 144) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_9C[(((int)&((Recovered_PhysicsScene *)0)->field_9C) == 156) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_A8[(((int)&((Recovered_PhysicsScene *)0)->field_A8) == 168) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_AC[(((int)&((Recovered_PhysicsScene *)0)->field_AC) == 172) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_B0[(((int)&((Recovered_PhysicsScene *)0)->field_B0) == 176) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_B4[(((int)&((Recovered_PhysicsScene *)0)->field_B4) == 180) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_B8[(((int)&((Recovered_PhysicsScene *)0)->field_B8) == 184) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_BC[(((int)&((Recovered_PhysicsScene *)0)->field_BC) == 188) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_C0[(((int)&((Recovered_PhysicsScene *)0)->field_C0) == 192) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_C8[(((int)&((Recovered_PhysicsScene *)0)->field_C8) == 200) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_CC[(((int)&((Recovered_PhysicsScene *)0)->field_CC) == 204) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_D4[(((int)&((Recovered_PhysicsScene *)0)->field_D4) == 212) ? 1 : -1];
typedef char assert_Recovered_PhysicsScene_D8[(((int)&((Recovered_PhysicsScene *)0)->field_D8) == 216) ? 1 : -1];
#endif
