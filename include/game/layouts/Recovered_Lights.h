/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_LIGHTS_H
#define RECOVERED_LIGHTS_H
#include "ps2/prelude.h"

typedef struct Recovered_Lights {
    u8 opaque_0[64];
    s32 field_40; /* PS2 +0x40 */
    u8 opaque_44[92];
    s32 field_A0; /* PS2 +0xA0 */
    u8 opaque_A4[92];
    s32 field_100; /* PS2 +0x100 */
    u8 opaque_104[92];
    s32 field_160; /* PS2 +0x160 */
    u8 opaque_164[92];
    s32 field_1C0; /* PS2 +0x1C0 */
    u8 opaque_1C4[92];
    s32 field_220; /* PS2 +0x220 */
    u8 opaque_224[92];
    s32 field_280; /* PS2 +0x280 */
    u8 opaque_284[92];
    s32 field_2E0; /* PS2 +0x2E0 */
    u8 opaque_2E4[92];
    s32 field_340; /* PS2 +0x340 */
    u8 opaque_344[23740];
    void * field_6000; /* PS2 +0x6000 */
    s32 field_6004; /* PS2 +0x6004 */
    s32 field_6008; /* PS2 +0x6008 */
    u16 field_600C; /* PS2 +0x600C */
} Recovered_Lights;
typedef char assert_Recovered_Lights_40[(((int)&((Recovered_Lights *)0)->field_40) == 64) ? 1 : -1];
typedef char assert_Recovered_Lights_A0[(((int)&((Recovered_Lights *)0)->field_A0) == 160) ? 1 : -1];
typedef char assert_Recovered_Lights_100[(((int)&((Recovered_Lights *)0)->field_100) == 256) ? 1 : -1];
typedef char assert_Recovered_Lights_160[(((int)&((Recovered_Lights *)0)->field_160) == 352) ? 1 : -1];
typedef char assert_Recovered_Lights_1C0[(((int)&((Recovered_Lights *)0)->field_1C0) == 448) ? 1 : -1];
typedef char assert_Recovered_Lights_220[(((int)&((Recovered_Lights *)0)->field_220) == 544) ? 1 : -1];
typedef char assert_Recovered_Lights_280[(((int)&((Recovered_Lights *)0)->field_280) == 640) ? 1 : -1];
typedef char assert_Recovered_Lights_2E0[(((int)&((Recovered_Lights *)0)->field_2E0) == 736) ? 1 : -1];
typedef char assert_Recovered_Lights_340[(((int)&((Recovered_Lights *)0)->field_340) == 832) ? 1 : -1];
typedef char assert_Recovered_Lights_6000[(((int)&((Recovered_Lights *)0)->field_6000) == 24576) ? 1 : -1];
typedef char assert_Recovered_Lights_6004[(((int)&((Recovered_Lights *)0)->field_6004) == 24580) ? 1 : -1];
typedef char assert_Recovered_Lights_6008[(((int)&((Recovered_Lights *)0)->field_6008) == 24584) ? 1 : -1];
typedef char assert_Recovered_Lights_600C[(((int)&((Recovered_Lights *)0)->field_600C) == 24588) ? 1 : -1];
#endif
