/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_QUERY_H
#define RECOVERED_QUERY_H
#include "ps2/prelude.h"

typedef struct Recovered_Query {
    u8 opaque_0[4];
    void * field_4; /* PS2 +0x4 */
} Recovered_Query;
typedef char assert_Recovered_Query_4[(((int)&((Recovered_Query *)0)->field_4) == 4) ? 1 : -1];
#endif
