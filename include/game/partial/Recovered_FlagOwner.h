/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_FLAGOWNER_H
#define RECOVERED_FLAGOWNER_H
#include "ps2/prelude.h"

typedef struct Recovered_FlagOwner {
    u8 opaque_0[20];
    u8 field_14; /* PS2 +0x14 */
} Recovered_FlagOwner;
typedef char assert_Recovered_FlagOwner_14[(((int)&((Recovered_FlagOwner *)0)->field_14) == 20) ? 1 : -1];
#endif
