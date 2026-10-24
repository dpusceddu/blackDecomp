/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PATHWAY_H
#define RECOVERED_PATHWAY_H
#include "ps2/prelude.h"

typedef struct Recovered_PathWay {
    void * field_0; /* PS2 +0x0 */
    void * field_4; /* PS2 +0x4 */
    s32 field_8; /* PS2 +0x8 */
    u8 field_C; /* PS2 +0xC */
    u8 opaque_D[259];
    s32 field_110; /* PS2 +0x110 */
} Recovered_PathWay;
typedef char assert_Recovered_PathWay_0[(((int)&((Recovered_PathWay *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_PathWay_4[(((int)&((Recovered_PathWay *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_PathWay_8[(((int)&((Recovered_PathWay *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_PathWay_C[(((int)&((Recovered_PathWay *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_PathWay_110[(((int)&((Recovered_PathWay *)0)->field_110) == 272) ? 1 : -1];
#endif
