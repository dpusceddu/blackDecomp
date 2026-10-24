/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_CHAIN50_H
#define RECOVERED_CHAIN50_H
#include "ps2/prelude.h"

typedef struct Recovered_Chain50 {
    u8 opaque_0[76];
    s32 field_4C; /* PS2 +0x4C */
    s32 field_50; /* PS2 +0x50 */
} Recovered_Chain50;
typedef char assert_Recovered_Chain50_4C[(((int)&((Recovered_Chain50 *)0)->field_4C) == 76) ? 1 : -1];
typedef char assert_Recovered_Chain50_50[(((int)&((Recovered_Chain50 *)0)->field_50) == 80) ? 1 : -1];
#endif
