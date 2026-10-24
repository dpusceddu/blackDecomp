/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003E22C0_H
#define RECOVERED_VTABLE_003E22C0_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003E22C0 {
    u8 opaque_0[4];
    u32 field_4; /* PS2 +0x4 */
    void * field_8; /* PS2 +0x8 */
    u32 field_C; /* PS2 +0xC */
} Recovered_Vtable_003E22C0;
typedef char assert_Recovered_Vtable_003E22C0_4[(((int)&((Recovered_Vtable_003E22C0 *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E22C0_8[(((int)&((Recovered_Vtable_003E22C0 *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E22C0_C[(((int)&((Recovered_Vtable_003E22C0 *)0)->field_C) == 12) ? 1 : -1];
#endif
