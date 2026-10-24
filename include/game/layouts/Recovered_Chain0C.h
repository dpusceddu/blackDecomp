/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_CHAIN0C_H
#define RECOVERED_CHAIN0C_H
#include "ps2/prelude.h"

typedef struct Recovered_Chain0C {
    u8 opaque_0[12];
    s32 field_C; /* PS2 +0xC */
    u8 opaque_10[4];
    s32 field_14; /* PS2 +0x14 */
} Recovered_Chain0C;
typedef char assert_Recovered_Chain0C_C[(((int)&((Recovered_Chain0C *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_Chain0C_14[(((int)&((Recovered_Chain0C *)0)->field_14) == 20) ? 1 : -1];
#endif
