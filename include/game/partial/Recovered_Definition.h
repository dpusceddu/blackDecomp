/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_DEFINITION_H
#define RECOVERED_DEFINITION_H
#include "ps2/prelude.h"

typedef struct Recovered_Definition {
    u8 opaque_0[32];
    s64 field_20; /* PS2 +0x20 */
} Recovered_Definition;
typedef char assert_Recovered_Definition_20[(((int)&((Recovered_Definition *)0)->field_20) == 32) ? 1 : -1];
#endif
