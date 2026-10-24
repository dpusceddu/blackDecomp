/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_QUERYGRAPH_H
#define RECOVERED_QUERYGRAPH_H
#include "ps2/prelude.h"

typedef struct Recovered_QueryGraph {
    u8 opaque_0[4];
    s32 field_4; /* PS2 +0x4 */
} Recovered_QueryGraph;
typedef char assert_Recovered_QueryGraph_4[(((int)&((Recovered_QueryGraph *)0)->field_4) == 4) ? 1 : -1];
#endif
