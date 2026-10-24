/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003E2818_H
#define RECOVERED_VTABLE_003E2818_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003E2818 {
    u8 opaque_0[16];
    s128 field_10; /* PS2 +0x10 */
    s128 field_20; /* PS2 +0x20 */
    s128 field_30; /* PS2 +0x30 */
    s128 field_40; /* PS2 +0x40 */
    u8 opaque_50[32];
    void * field_70; /* PS2 +0x70 */
} Recovered_Vtable_003E2818;
typedef char assert_Recovered_Vtable_003E2818_10[(((int)&((Recovered_Vtable_003E2818 *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E2818_20[(((int)&((Recovered_Vtable_003E2818 *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E2818_30[(((int)&((Recovered_Vtable_003E2818 *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E2818_40[(((int)&((Recovered_Vtable_003E2818 *)0)->field_40) == 64) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E2818_70[(((int)&((Recovered_Vtable_003E2818 *)0)->field_70) == 112) ? 1 : -1];
#endif
