/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RESERVES_H
#define RECOVERED_RESERVES_H
#include "ps2/prelude.h"

typedef struct Recovered_Reserves {
    u8 opaque_0[20];
    s32 field_14; /* PS2 +0x14 */
    s8 field_18; /* PS2 +0x18 */
} Recovered_Reserves;
typedef char assert_Recovered_Reserves_14[(((int)&((Recovered_Reserves *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_Reserves_18[(((int)&((Recovered_Reserves *)0)->field_18) == 24) ? 1 : -1];
#endif
