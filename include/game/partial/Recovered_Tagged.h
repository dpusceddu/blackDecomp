/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_TAGGED_H
#define RECOVERED_TAGGED_H
#include "ps2/prelude.h"

typedef struct Recovered_Tagged {
    u32 field_0; /* PS2 +0x0 */
    u32 field_4; /* PS2 +0x4 */
} Recovered_Tagged;
typedef char assert_Recovered_Tagged_0[(((int)&((Recovered_Tagged *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Tagged_4[(((int)&((Recovered_Tagged *)0)->field_4) == 4) ? 1 : -1];
#endif
