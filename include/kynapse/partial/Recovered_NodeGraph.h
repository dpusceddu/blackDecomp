/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_NODEGRAPH_H
#define RECOVERED_NODEGRAPH_H
#include "ps2/prelude.h"

typedef struct Recovered_NodeGraph {
    u8 opaque_0[8];
    f32 field_8; /* PS2 +0x8 */
    s32 field_C; /* PS2 +0xC */
    u8 opaque_10[4];
    s32 field_14; /* PS2 +0x14 */
    s32 field_18; /* PS2 +0x18 */
} Recovered_NodeGraph;
typedef char assert_Recovered_NodeGraph_8[(((int)&((Recovered_NodeGraph *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_NodeGraph_C[(((int)&((Recovered_NodeGraph *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_NodeGraph_14[(((int)&((Recovered_NodeGraph *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_NodeGraph_18[(((int)&((Recovered_NodeGraph *)0)->field_18) == 24) ? 1 : -1];
#endif
