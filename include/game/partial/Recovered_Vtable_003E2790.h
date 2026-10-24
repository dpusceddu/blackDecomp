/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003E2790_H
#define RECOVERED_VTABLE_003E2790_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003E2790 {
    u8 opaque_0[48];
    u8 field_30; /* PS2 +0x30 */
    u8 opaque_31[7];
    void * field_38; /* PS2 +0x38 */
} Recovered_Vtable_003E2790;
typedef char assert_Recovered_Vtable_003E2790_30[(((int)&((Recovered_Vtable_003E2790 *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E2790_38[(((int)&((Recovered_Vtable_003E2790 *)0)->field_38) == 56) ? 1 : -1];
#endif
