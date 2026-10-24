/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DE670_H
#define RECOVERED_VTABLE_003DE670_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DE670 {
    void * field_0; /* PS2 +0x0 */
    u8 opaque_4[12];
    u128 field_10; /* PS2 +0x10 */
    u8 opaque_20[24];
    s32 field_38; /* PS2 +0x38 */
    u8 field_3C; /* PS2 +0x3C */
} Recovered_Vtable_003DE670;
typedef char assert_Recovered_Vtable_003DE670_0[(((int)&((Recovered_Vtable_003DE670 *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DE670_10[(((int)&((Recovered_Vtable_003DE670 *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DE670_38[(((int)&((Recovered_Vtable_003DE670 *)0)->field_38) == 56) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DE670_3C[(((int)&((Recovered_Vtable_003DE670 *)0)->field_3C) == 60) ? 1 : -1];
#endif
