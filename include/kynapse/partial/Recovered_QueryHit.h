/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_QUERYHIT_H
#define RECOVERED_QUERYHIT_H
#include "ps2/prelude.h"

typedef struct Recovered_QueryHit {
    s128 field_0; /* PS2 +0x0 */
    s128 field_10; /* PS2 +0x10 */
    u8 opaque_20[48];
    f32 field_50; /* PS2 +0x50 */
    u8 opaque_54[12];
    void * field_60; /* PS2 +0x60 */
} Recovered_QueryHit;
typedef char assert_Recovered_QueryHit_0[(((int)&((Recovered_QueryHit *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_QueryHit_10[(((int)&((Recovered_QueryHit *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_QueryHit_50[(((int)&((Recovered_QueryHit *)0)->field_50) == 80) ? 1 : -1];
typedef char assert_Recovered_QueryHit_60[(((int)&((Recovered_QueryHit *)0)->field_60) == 96) ? 1 : -1];
#endif
