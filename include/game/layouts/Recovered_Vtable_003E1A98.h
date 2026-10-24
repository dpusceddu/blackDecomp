/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003E1A98_H
#define RECOVERED_VTABLE_003E1A98_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003E1A98 {
    u8 opaque_0[4];
    u32 field_4; /* PS2 +0x4 */
    u8 opaque_8[40];
    s32 field_30; /* PS2 +0x30 */
    s32 field_34; /* PS2 +0x34 */
    s32 field_38; /* PS2 +0x38 */
} Recovered_Vtable_003E1A98;
typedef char assert_Recovered_Vtable_003E1A98_4[(((int)&((Recovered_Vtable_003E1A98 *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E1A98_30[(((int)&((Recovered_Vtable_003E1A98 *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E1A98_34[(((int)&((Recovered_Vtable_003E1A98 *)0)->field_34) == 52) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E1A98_38[(((int)&((Recovered_Vtable_003E1A98 *)0)->field_38) == 56) ? 1 : -1];
#endif
