/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_GEOMETRYNODES_H
#define RECOVERED_GEOMETRYNODES_H
#include "ps2/prelude.h"

typedef struct Recovered_GeometryNodes {
    u8 field_0; /* PS2 +0x0 */
    u8 opaque_1[131];
    u32 field_84; /* PS2 +0x84 */
    u8 field_88; /* PS2 +0x88 */
    u8 opaque_89[131];
    u32 field_10C; /* PS2 +0x10C */
    u8 field_110; /* PS2 +0x110 */
    u8 opaque_111[131];
    u32 field_194; /* PS2 +0x194 */
    u8 field_198; /* PS2 +0x198 */
    u8 opaque_199[131];
    u32 field_21C; /* PS2 +0x21C */
    u8 field_220; /* PS2 +0x220 */
    u8 opaque_221[131];
    u32 field_2A4; /* PS2 +0x2A4 */
    u8 field_2A8; /* PS2 +0x2A8 */
    u8 opaque_2A9[131];
    u32 field_32C; /* PS2 +0x32C */
    u8 field_330; /* PS2 +0x330 */
    u8 opaque_331[131];
    u32 field_3B4; /* PS2 +0x3B4 */
    u8 field_3B8; /* PS2 +0x3B8 */
    u8 opaque_3B9[131];
    u32 field_43C; /* PS2 +0x43C */
    u8 opaque_440[4];
    u32 field_444; /* PS2 +0x444 */
    u32 field_448; /* PS2 +0x448 */
    u32 field_44C; /* PS2 +0x44C */
    u32 field_450; /* PS2 +0x450 */
    u32 field_454; /* PS2 +0x454 */
    u32 field_458; /* PS2 +0x458 */
    u32 field_45C; /* PS2 +0x45C */
    u8 opaque_460[16];
    u32 field_470; /* PS2 +0x470 */
    u32 field_474; /* PS2 +0x474 */
    u32 field_478; /* PS2 +0x478 */
    u32 field_47C; /* PS2 +0x47C */
    u32 field_480; /* PS2 +0x480 */
    u32 field_484; /* PS2 +0x484 */
    u32 field_488; /* PS2 +0x488 */
    u32 field_48C; /* PS2 +0x48C */
} Recovered_GeometryNodes;
typedef char assert_Recovered_GeometryNodes_0[(((int)&((Recovered_GeometryNodes *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_84[(((int)&((Recovered_GeometryNodes *)0)->field_84) == 132) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_88[(((int)&((Recovered_GeometryNodes *)0)->field_88) == 136) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_10C[(((int)&((Recovered_GeometryNodes *)0)->field_10C) == 268) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_110[(((int)&((Recovered_GeometryNodes *)0)->field_110) == 272) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_194[(((int)&((Recovered_GeometryNodes *)0)->field_194) == 404) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_198[(((int)&((Recovered_GeometryNodes *)0)->field_198) == 408) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_21C[(((int)&((Recovered_GeometryNodes *)0)->field_21C) == 540) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_220[(((int)&((Recovered_GeometryNodes *)0)->field_220) == 544) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_2A4[(((int)&((Recovered_GeometryNodes *)0)->field_2A4) == 676) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_2A8[(((int)&((Recovered_GeometryNodes *)0)->field_2A8) == 680) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_32C[(((int)&((Recovered_GeometryNodes *)0)->field_32C) == 812) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_330[(((int)&((Recovered_GeometryNodes *)0)->field_330) == 816) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_3B4[(((int)&((Recovered_GeometryNodes *)0)->field_3B4) == 948) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_3B8[(((int)&((Recovered_GeometryNodes *)0)->field_3B8) == 952) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_43C[(((int)&((Recovered_GeometryNodes *)0)->field_43C) == 1084) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_444[(((int)&((Recovered_GeometryNodes *)0)->field_444) == 1092) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_448[(((int)&((Recovered_GeometryNodes *)0)->field_448) == 1096) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_44C[(((int)&((Recovered_GeometryNodes *)0)->field_44C) == 1100) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_450[(((int)&((Recovered_GeometryNodes *)0)->field_450) == 1104) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_454[(((int)&((Recovered_GeometryNodes *)0)->field_454) == 1108) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_458[(((int)&((Recovered_GeometryNodes *)0)->field_458) == 1112) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_45C[(((int)&((Recovered_GeometryNodes *)0)->field_45C) == 1116) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_470[(((int)&((Recovered_GeometryNodes *)0)->field_470) == 1136) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_474[(((int)&((Recovered_GeometryNodes *)0)->field_474) == 1140) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_478[(((int)&((Recovered_GeometryNodes *)0)->field_478) == 1144) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_47C[(((int)&((Recovered_GeometryNodes *)0)->field_47C) == 1148) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_480[(((int)&((Recovered_GeometryNodes *)0)->field_480) == 1152) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_484[(((int)&((Recovered_GeometryNodes *)0)->field_484) == 1156) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_488[(((int)&((Recovered_GeometryNodes *)0)->field_488) == 1160) ? 1 : -1];
typedef char assert_Recovered_GeometryNodes_48C[(((int)&((Recovered_GeometryNodes *)0)->field_48C) == 1164) ? 1 : -1];
#endif
