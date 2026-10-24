/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ROUTEBLOCK_H
#define RECOVERED_ROUTEBLOCK_H
#include "ps2/prelude.h"

typedef struct Recovered_RouteBlock {
    u32 field_0; /* PS2 +0x0 */
    u8 opaque_4[8];
    s32 field_C; /* PS2 +0xC */
    s32 field_10; /* PS2 +0x10 */
    s32 field_14; /* PS2 +0x14 */
    s32 field_18; /* PS2 +0x18 */
} Recovered_RouteBlock;
typedef char assert_Recovered_RouteBlock_0[(((int)&((Recovered_RouteBlock *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_RouteBlock_C[(((int)&((Recovered_RouteBlock *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_RouteBlock_10[(((int)&((Recovered_RouteBlock *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_RouteBlock_14[(((int)&((Recovered_RouteBlock *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_RouteBlock_18[(((int)&((Recovered_RouteBlock *)0)->field_18) == 24) ? 1 : -1];
#endif
