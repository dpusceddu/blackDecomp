/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_NEARESTSIMPLEVISITOR_H
#define RECOVERED_NEARESTSIMPLEVISITOR_H
#include "ps2/prelude.h"

typedef struct Recovered_NearestSimpleVisitor {
    u8 opaque_0[8];
    u64 field_8; /* PS2 +0x8 */
    u32 field_10; /* PS2 +0x10 */
} Recovered_NearestSimpleVisitor;
typedef char assert_Recovered_NearestSimpleVisitor_8[(((int)&((Recovered_NearestSimpleVisitor *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_NearestSimpleVisitor_10[(((int)&((Recovered_NearestSimpleVisitor *)0)->field_10) == 16) ? 1 : -1];
#endif
