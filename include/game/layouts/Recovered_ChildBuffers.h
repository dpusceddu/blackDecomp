/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_CHILDBUFFERS_H
#define RECOVERED_CHILDBUFFERS_H
#include "ps2/prelude.h"

typedef struct Recovered_ChildBuffers {
    void * field_0; /* PS2 +0x0 */
    u32 field_4; /* PS2 +0x4 */
    u32 field_8; /* PS2 +0x8 */
    s32 field_C; /* PS2 +0xC */
    s32 field_10; /* PS2 +0x10 */
    s32 field_14; /* PS2 +0x14 */
    void * field_18; /* PS2 +0x18 */
    s32 field_1C; /* PS2 +0x1C */
    s32 field_20; /* PS2 +0x20 */
} Recovered_ChildBuffers;
typedef char assert_Recovered_ChildBuffers_0[(((int)&((Recovered_ChildBuffers *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_ChildBuffers_4[(((int)&((Recovered_ChildBuffers *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_ChildBuffers_8[(((int)&((Recovered_ChildBuffers *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_ChildBuffers_C[(((int)&((Recovered_ChildBuffers *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_ChildBuffers_10[(((int)&((Recovered_ChildBuffers *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_ChildBuffers_14[(((int)&((Recovered_ChildBuffers *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_ChildBuffers_18[(((int)&((Recovered_ChildBuffers *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_ChildBuffers_1C[(((int)&((Recovered_ChildBuffers *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_ChildBuffers_20[(((int)&((Recovered_ChildBuffers *)0)->field_20) == 32) ? 1 : -1];
#endif
