/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ROUTESTORAGE_H
#define RECOVERED_ROUTESTORAGE_H
#include "ps2/prelude.h"

typedef struct Recovered_RouteStorage {
    u8 opaque_0[4];
    s32 field_4; /* PS2 +0x4 */
    u32 field_8; /* PS2 +0x8 */
    u32 field_C; /* PS2 +0xC */
    u32 field_10; /* PS2 +0x10 */
    u32 field_14; /* PS2 +0x14 */
    u32 field_18; /* PS2 +0x18 */
    u32 field_1C; /* PS2 +0x1C */
    u8 field_20; /* PS2 +0x20 */
    u8 opaque_21[7];
} Recovered_RouteStorage;
typedef char assert_Recovered_RouteStorage_4[(((int)&((Recovered_RouteStorage *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_RouteStorage_8[(((int)&((Recovered_RouteStorage *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_RouteStorage_C[(((int)&((Recovered_RouteStorage *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_RouteStorage_10[(((int)&((Recovered_RouteStorage *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_RouteStorage_14[(((int)&((Recovered_RouteStorage *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_RouteStorage_18[(((int)&((Recovered_RouteStorage *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_RouteStorage_1C[(((int)&((Recovered_RouteStorage *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_RouteStorage_20[(((int)&((Recovered_RouteStorage *)0)->field_20) == 32) ? 1 : -1];
#endif
