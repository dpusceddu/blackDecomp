/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003E2588_H
#define RECOVERED_VTABLE_003E2588_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003E2588 {
    u8 opaque_0[256];
    s32 field_100; /* PS2 +0x100 */
    u8 opaque_104[16];
    s32 field_114; /* PS2 +0x114 */
} Recovered_Vtable_003E2588;
typedef char assert_Recovered_Vtable_003E2588_100[(((int)&((Recovered_Vtable_003E2588 *)0)->field_100) == 256) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E2588_114[(((int)&((Recovered_Vtable_003E2588 *)0)->field_114) == 276) ? 1 : -1];
#endif
