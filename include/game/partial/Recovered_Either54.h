/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_EITHER54_H
#define RECOVERED_EITHER54_H
#include "ps2/prelude.h"

typedef struct Recovered_Either54 {
    u8 opaque_0[84];
    s32 field_54; /* PS2 +0x54 */
    s32 field_58; /* PS2 +0x58 */
    s32 field_5C; /* PS2 +0x5C */
} Recovered_Either54;
typedef char assert_Recovered_Either54_54[(((int)&((Recovered_Either54 *)0)->field_54) == 84) ? 1 : -1];
typedef char assert_Recovered_Either54_58[(((int)&((Recovered_Either54 *)0)->field_58) == 88) ? 1 : -1];
typedef char assert_Recovered_Either54_5C[(((int)&((Recovered_Either54 *)0)->field_5C) == 92) ? 1 : -1];
#endif
