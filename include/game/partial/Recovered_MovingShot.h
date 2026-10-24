/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_MOVINGSHOT_H
#define RECOVERED_MOVINGSHOT_H
#include "ps2/prelude.h"

typedef struct Recovered_MovingShot {
    u128 field_0; /* PS2 +0x0 */
    u8 opaque_10[16];
    f32 field_20; /* PS2 +0x20 */
    void * field_24; /* PS2 +0x24 */
    s32 field_28; /* PS2 +0x28 */
    u8 opaque_2C[20];
    s128 field_40; /* PS2 +0x40 */
    u128 field_50; /* PS2 +0x50 */
    u128 field_60; /* PS2 +0x60 */
    void * field_70; /* PS2 +0x70 */
    u8 opaque_74[8];
    f32 field_7C; /* PS2 +0x7C */
    s8 field_80; /* PS2 +0x80 */
    u8 opaque_81[3];
    f32 field_84; /* PS2 +0x84 */
    u8 field_88; /* PS2 +0x88 */
    u8 field_89; /* PS2 +0x89 */
    u8 field_8A; /* PS2 +0x8A */
    u8 field_8B; /* PS2 +0x8B */
    u8 field_8C; /* PS2 +0x8C */
} Recovered_MovingShot;
typedef char assert_Recovered_MovingShot_0[(((int)&((Recovered_MovingShot *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_MovingShot_20[(((int)&((Recovered_MovingShot *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_MovingShot_24[(((int)&((Recovered_MovingShot *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_MovingShot_28[(((int)&((Recovered_MovingShot *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_MovingShot_40[(((int)&((Recovered_MovingShot *)0)->field_40) == 64) ? 1 : -1];
typedef char assert_Recovered_MovingShot_50[(((int)&((Recovered_MovingShot *)0)->field_50) == 80) ? 1 : -1];
typedef char assert_Recovered_MovingShot_60[(((int)&((Recovered_MovingShot *)0)->field_60) == 96) ? 1 : -1];
typedef char assert_Recovered_MovingShot_70[(((int)&((Recovered_MovingShot *)0)->field_70) == 112) ? 1 : -1];
typedef char assert_Recovered_MovingShot_7C[(((int)&((Recovered_MovingShot *)0)->field_7C) == 124) ? 1 : -1];
typedef char assert_Recovered_MovingShot_80[(((int)&((Recovered_MovingShot *)0)->field_80) == 128) ? 1 : -1];
typedef char assert_Recovered_MovingShot_84[(((int)&((Recovered_MovingShot *)0)->field_84) == 132) ? 1 : -1];
typedef char assert_Recovered_MovingShot_88[(((int)&((Recovered_MovingShot *)0)->field_88) == 136) ? 1 : -1];
typedef char assert_Recovered_MovingShot_89[(((int)&((Recovered_MovingShot *)0)->field_89) == 137) ? 1 : -1];
typedef char assert_Recovered_MovingShot_8A[(((int)&((Recovered_MovingShot *)0)->field_8A) == 138) ? 1 : -1];
typedef char assert_Recovered_MovingShot_8B[(((int)&((Recovered_MovingShot *)0)->field_8B) == 139) ? 1 : -1];
typedef char assert_Recovered_MovingShot_8C[(((int)&((Recovered_MovingShot *)0)->field_8C) == 140) ? 1 : -1];
#endif
