/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ACTORENTRIES_H
#define RECOVERED_ACTORENTRIES_H
#include "ps2/prelude.h"

typedef struct Recovered_ActorEntries {
    u8 opaque_0[16];
    void * field_10; /* PS2 +0x10 */
    u8 opaque_14[160];
    s32 field_B4; /* PS2 +0xB4 */
    u8 opaque_B8[96];
    s32 field_118; /* PS2 +0x118 */
    u8 opaque_11C[8];
    u32 field_124; /* PS2 +0x124 */
    u8 opaque_128[20];
    u8 field_13C; /* PS2 +0x13C */
    u8 opaque_13D[99];
    s32 field_1A0; /* PS2 +0x1A0 */
    u8 opaque_1A4[4];
    s32 field_1A8; /* PS2 +0x1A8 */
    s32 field_1AC; /* PS2 +0x1AC */
    u8 opaque_1B0[8];
    s32 field_1B8; /* PS2 +0x1B8 */
    u8 opaque_1BC[48];
    u8 field_1EC; /* PS2 +0x1EC */
    u8 field_1ED; /* PS2 +0x1ED */
    u8 opaque_1EE[2];
    s32 field_1F0; /* PS2 +0x1F0 */
    u8 opaque_1F4[1];
    u8 field_1F5; /* PS2 +0x1F5 */
} Recovered_ActorEntries;
typedef char assert_Recovered_ActorEntries_10[(((int)&((Recovered_ActorEntries *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_ActorEntries_B4[(((int)&((Recovered_ActorEntries *)0)->field_B4) == 180) ? 1 : -1];
typedef char assert_Recovered_ActorEntries_118[(((int)&((Recovered_ActorEntries *)0)->field_118) == 280) ? 1 : -1];
typedef char assert_Recovered_ActorEntries_124[(((int)&((Recovered_ActorEntries *)0)->field_124) == 292) ? 1 : -1];
typedef char assert_Recovered_ActorEntries_13C[(((int)&((Recovered_ActorEntries *)0)->field_13C) == 316) ? 1 : -1];
typedef char assert_Recovered_ActorEntries_1A0[(((int)&((Recovered_ActorEntries *)0)->field_1A0) == 416) ? 1 : -1];
typedef char assert_Recovered_ActorEntries_1A8[(((int)&((Recovered_ActorEntries *)0)->field_1A8) == 424) ? 1 : -1];
typedef char assert_Recovered_ActorEntries_1AC[(((int)&((Recovered_ActorEntries *)0)->field_1AC) == 428) ? 1 : -1];
typedef char assert_Recovered_ActorEntries_1B8[(((int)&((Recovered_ActorEntries *)0)->field_1B8) == 440) ? 1 : -1];
typedef char assert_Recovered_ActorEntries_1EC[(((int)&((Recovered_ActorEntries *)0)->field_1EC) == 492) ? 1 : -1];
typedef char assert_Recovered_ActorEntries_1ED[(((int)&((Recovered_ActorEntries *)0)->field_1ED) == 493) ? 1 : -1];
typedef char assert_Recovered_ActorEntries_1F0[(((int)&((Recovered_ActorEntries *)0)->field_1F0) == 496) ? 1 : -1];
typedef char assert_Recovered_ActorEntries_1F5[(((int)&((Recovered_ActorEntries *)0)->field_1F5) == 501) ? 1 : -1];
#endif
