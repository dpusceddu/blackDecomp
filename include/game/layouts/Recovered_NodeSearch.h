/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_NODESEARCH_H
#define RECOVERED_NODESEARCH_H
#include "ps2/prelude.h"

typedef struct Recovered_NodeSearch {
    s32 field_0; /* PS2 +0x0 */
    u8 opaque_4[12];
    s128 field_10; /* PS2 +0x10 */
    s32 field_20; /* PS2 +0x20 */
    s32 field_24; /* PS2 +0x24 */
    u8 opaque_28[252];
    s32 field_124; /* PS2 +0x124 */
    u8 field_128; /* PS2 +0x128 */
} Recovered_NodeSearch;
typedef char assert_Recovered_NodeSearch_0[(((int)&((Recovered_NodeSearch *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_NodeSearch_10[(((int)&((Recovered_NodeSearch *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_NodeSearch_20[(((int)&((Recovered_NodeSearch *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_NodeSearch_24[(((int)&((Recovered_NodeSearch *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_NodeSearch_124[(((int)&((Recovered_NodeSearch *)0)->field_124) == 292) ? 1 : -1];
typedef char assert_Recovered_NodeSearch_128[(((int)&((Recovered_NodeSearch *)0)->field_128) == 296) ? 1 : -1];
#endif
