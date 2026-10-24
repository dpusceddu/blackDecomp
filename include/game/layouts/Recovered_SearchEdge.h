/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_SEARCHEDGE_H
#define RECOVERED_SEARCHEDGE_H
#include "ps2/prelude.h"

typedef struct Recovered_SearchEdge {
    s32 field_0; /* PS2 +0x0 */
    void * field_4; /* PS2 +0x4 */
} Recovered_SearchEdge;
typedef char assert_Recovered_SearchEdge_0[(((int)&((Recovered_SearchEdge *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_SearchEdge_4[(((int)&((Recovered_SearchEdge *)0)->field_4) == 4) ? 1 : -1];
#endif
