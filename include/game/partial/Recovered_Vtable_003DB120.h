/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DB120_H
#define RECOVERED_VTABLE_003DB120_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DB120 {
    u8 opaque_0[32];
    s128 field_20; /* PS2 +0x20 */
    u128 field_30; /* PS2 +0x30 */
} Recovered_Vtable_003DB120;
typedef char assert_Recovered_Vtable_003DB120_20[(((int)&((Recovered_Vtable_003DB120 *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB120_30[(((int)&((Recovered_Vtable_003DB120 *)0)->field_30) == 48) ? 1 : -1];
#endif
