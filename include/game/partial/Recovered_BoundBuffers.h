/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_BOUNDBUFFERS_H
#define RECOVERED_BOUNDBUFFERS_H
#include "ps2/prelude.h"

typedef struct Recovered_BoundBuffers {
    u32 field_0; /* PS2 +0x0 */
    u32 field_4; /* PS2 +0x4 */
    u32 field_8; /* PS2 +0x8 */
    u32 field_C; /* PS2 +0xC */
    u32 field_10; /* PS2 +0x10 */
    u32 field_14; /* PS2 +0x14 */
    u32 field_18; /* PS2 +0x18 */
} Recovered_BoundBuffers;
typedef char assert_Recovered_BoundBuffers_0[(((int)&((Recovered_BoundBuffers *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_BoundBuffers_4[(((int)&((Recovered_BoundBuffers *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_BoundBuffers_8[(((int)&((Recovered_BoundBuffers *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_BoundBuffers_C[(((int)&((Recovered_BoundBuffers *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_BoundBuffers_10[(((int)&((Recovered_BoundBuffers *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_BoundBuffers_14[(((int)&((Recovered_BoundBuffers *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_BoundBuffers_18[(((int)&((Recovered_BoundBuffers *)0)->field_18) == 24) ? 1 : -1];
#endif
