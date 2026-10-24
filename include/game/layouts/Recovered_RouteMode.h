/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ROUTEMODE_H
#define RECOVERED_ROUTEMODE_H
#include "ps2/prelude.h"

typedef struct Recovered_RouteMode {
    f32 field_0; /* PS2 +0x0 */
    f32 field_4; /* PS2 +0x4 */
    u8 opaque_8[8];
    s128 field_10; /* PS2 +0x10 */
    u8 opaque_20[16];
    s32 field_30; /* PS2 +0x30 */
    void * field_34; /* PS2 +0x34 */
    u8 opaque_38[4];
    f32 field_3C; /* PS2 +0x3C */
    u8 opaque_40[48];
    u128 field_70; /* PS2 +0x70 */
    void * field_80; /* PS2 +0x80 */
    u8 opaque_84[12];
    void * field_90; /* PS2 +0x90 */
    u8 field_94; /* PS2 +0x94 */
    u8 field_95; /* PS2 +0x95 */
    u8 opaque_96[2];
    u32 field_98; /* PS2 +0x98 */
    u8 opaque_9C[228];
    void * field_180; /* PS2 +0x180 */
    void * field_184; /* PS2 +0x184 */
} Recovered_RouteMode;
typedef char assert_Recovered_RouteMode_0[(((int)&((Recovered_RouteMode *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_RouteMode_4[(((int)&((Recovered_RouteMode *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_RouteMode_10[(((int)&((Recovered_RouteMode *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_RouteMode_30[(((int)&((Recovered_RouteMode *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_RouteMode_34[(((int)&((Recovered_RouteMode *)0)->field_34) == 52) ? 1 : -1];
typedef char assert_Recovered_RouteMode_3C[(((int)&((Recovered_RouteMode *)0)->field_3C) == 60) ? 1 : -1];
typedef char assert_Recovered_RouteMode_70[(((int)&((Recovered_RouteMode *)0)->field_70) == 112) ? 1 : -1];
typedef char assert_Recovered_RouteMode_80[(((int)&((Recovered_RouteMode *)0)->field_80) == 128) ? 1 : -1];
typedef char assert_Recovered_RouteMode_90[(((int)&((Recovered_RouteMode *)0)->field_90) == 144) ? 1 : -1];
typedef char assert_Recovered_RouteMode_94[(((int)&((Recovered_RouteMode *)0)->field_94) == 148) ? 1 : -1];
typedef char assert_Recovered_RouteMode_95[(((int)&((Recovered_RouteMode *)0)->field_95) == 149) ? 1 : -1];
typedef char assert_Recovered_RouteMode_98[(((int)&((Recovered_RouteMode *)0)->field_98) == 152) ? 1 : -1];
typedef char assert_Recovered_RouteMode_180[(((int)&((Recovered_RouteMode *)0)->field_180) == 384) ? 1 : -1];
typedef char assert_Recovered_RouteMode_184[(((int)&((Recovered_RouteMode *)0)->field_184) == 388) ? 1 : -1];
#endif
