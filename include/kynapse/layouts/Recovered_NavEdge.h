/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_NAVEDGE_H
#define RECOVERED_NAVEDGE_H
#include "ps2/prelude.h"

typedef struct Recovered_NavEdge {
    s32 field_0; /* PS2 +0x0 */
    void * field_4; /* PS2 +0x4 */
} Recovered_NavEdge;
typedef char assert_Recovered_NavEdge_0[(((int)&((Recovered_NavEdge *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_NavEdge_4[(((int)&((Recovered_NavEdge *)0)->field_4) == 4) ? 1 : -1];
#endif
