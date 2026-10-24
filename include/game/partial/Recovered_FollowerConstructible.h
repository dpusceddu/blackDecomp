/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_FOLLOWERCONSTRUCTIBLE_H
#define RECOVERED_FOLLOWERCONSTRUCTIBLE_H
#include "ps2/prelude.h"

typedef struct Recovered_FollowerConstructible {
    u32 field_0; /* PS2 +0x0 */
    u8 opaque_4[8];
    u32 field_C; /* PS2 +0xC */
    u32 field_10; /* PS2 +0x10 */
    u8 opaque_14[40];
    u32 field_3C; /* PS2 +0x3C */
} Recovered_FollowerConstructible;
typedef char assert_Recovered_FollowerConstructible_0[(((int)&((Recovered_FollowerConstructible *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_FollowerConstructible_C[(((int)&((Recovered_FollowerConstructible *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_FollowerConstructible_10[(((int)&((Recovered_FollowerConstructible *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_FollowerConstructible_3C[(((int)&((Recovered_FollowerConstructible *)0)->field_3C) == 60) ? 1 : -1];
#endif
