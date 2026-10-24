/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_IDHOLDER_H
#define RECOVERED_IDHOLDER_H
#include "ps2/prelude.h"

typedef struct Recovered_IdHolder {
    u8 opaque_0[4];
    u32 field_4; /* PS2 +0x4 */
} Recovered_IdHolder;
typedef char assert_Recovered_IdHolder_4[(((int)&((Recovered_IdHolder *)0)->field_4) == 4) ? 1 : -1];
#endif
