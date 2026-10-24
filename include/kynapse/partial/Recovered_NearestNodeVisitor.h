/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_NEARESTNODEVISITOR_H
#define RECOVERED_NEARESTNODEVISITOR_H
#include "ps2/prelude.h"

typedef struct Recovered_NearestNodeVisitor {
    u8 opaque_0[8];
    u64 field_8; /* PS2 +0x8 */
    u8 opaque_10[4];
    u32 field_14; /* PS2 +0x14 */
    u32 field_18; /* PS2 +0x18 */
} Recovered_NearestNodeVisitor;
typedef char assert_Recovered_NearestNodeVisitor_8[(((int)&((Recovered_NearestNodeVisitor *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_NearestNodeVisitor_14[(((int)&((Recovered_NearestNodeVisitor *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_NearestNodeVisitor_18[(((int)&((Recovered_NearestNodeVisitor *)0)->field_18) == 24) ? 1 : -1];
#endif
