/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_NEARESTEDGEVISITOR_H
#define RECOVERED_NEARESTEDGEVISITOR_H
#include "ps2/prelude.h"

typedef struct Recovered_NearestEdgeVisitor {
    u8 opaque_0[8];
    s64 field_8; /* PS2 +0x8 */
    f32 field_10; /* PS2 +0x10 */
    u32 field_14; /* PS2 +0x14 */
    f32 field_18; /* PS2 +0x18 */
    f32 field_1C; /* PS2 +0x1C */
    f32 field_20; /* PS2 +0x20 */
} Recovered_NearestEdgeVisitor;
typedef char assert_Recovered_NearestEdgeVisitor_8[(((int)&((Recovered_NearestEdgeVisitor *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_NearestEdgeVisitor_10[(((int)&((Recovered_NearestEdgeVisitor *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_NearestEdgeVisitor_14[(((int)&((Recovered_NearestEdgeVisitor *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_NearestEdgeVisitor_18[(((int)&((Recovered_NearestEdgeVisitor *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_NearestEdgeVisitor_1C[(((int)&((Recovered_NearestEdgeVisitor *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_NearestEdgeVisitor_20[(((int)&((Recovered_NearestEdgeVisitor *)0)->field_20) == 32) ? 1 : -1];
#endif
