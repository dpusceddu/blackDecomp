/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_SEARCHNODE_H
#define RECOVERED_SEARCHNODE_H
#include "ps2/prelude.h"

typedef struct Recovered_SearchNode {
    s32 field_0; /* PS2 +0x0 */
    u8 opaque_4[12];
    void * field_10; /* PS2 +0x10 */
} Recovered_SearchNode;
typedef char assert_Recovered_SearchNode_0[(((int)&((Recovered_SearchNode *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_SearchNode_10[(((int)&((Recovered_SearchNode *)0)->field_10) == 16) ? 1 : -1];
#endif
