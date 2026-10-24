/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003E1A10_H
#define RECOVERED_VTABLE_003E1A10_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003E1A10 {
    u8 opaque_0[4];
    u32 field_4; /* PS2 +0x4 */
    u8 opaque_8[24];
    s32 field_20; /* PS2 +0x20 */
    s32 field_24; /* PS2 +0x24 */
    s32 field_28; /* PS2 +0x28 */
} Recovered_Vtable_003E1A10;
typedef char assert_Recovered_Vtable_003E1A10_4[(((int)&((Recovered_Vtable_003E1A10 *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E1A10_20[(((int)&((Recovered_Vtable_003E1A10 *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E1A10_24[(((int)&((Recovered_Vtable_003E1A10 *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E1A10_28[(((int)&((Recovered_Vtable_003E1A10 *)0)->field_28) == 40) ? 1 : -1];
#endif
