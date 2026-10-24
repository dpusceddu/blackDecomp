/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DB710_H
#define RECOVERED_VTABLE_003DB710_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DB710 {
    u64 field_0; /* PS2 +0x0 */
    u8 opaque_8[16];
    u32 field_18; /* PS2 +0x18 */
    u8 field_1C; /* PS2 +0x1C */
    u8 opaque_1D[3];
    void * field_20; /* PS2 +0x20 */
} Recovered_Vtable_003DB710;
typedef char assert_Recovered_Vtable_003DB710_0[(((int)&((Recovered_Vtable_003DB710 *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB710_18[(((int)&((Recovered_Vtable_003DB710 *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB710_1C[(((int)&((Recovered_Vtable_003DB710 *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB710_20[(((int)&((Recovered_Vtable_003DB710 *)0)->field_20) == 32) ? 1 : -1];
#endif
