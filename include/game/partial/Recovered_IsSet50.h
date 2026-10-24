/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ISSET50_H
#define RECOVERED_ISSET50_H
#include "ps2/prelude.h"

typedef struct Recovered_IsSet50 {
    u8 opaque_0[80];
    s32 field_50; /* PS2 +0x50 */
} Recovered_IsSet50;
typedef char assert_Recovered_IsSet50_50[(((int)&((Recovered_IsSet50 *)0)->field_50) == 80) ? 1 : -1];
#endif
