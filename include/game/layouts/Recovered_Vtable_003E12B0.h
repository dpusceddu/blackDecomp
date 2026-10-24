/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003E12B0_H
#define RECOVERED_VTABLE_003E12B0_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003E12B0 {
    u8 opaque_0[12];
    s32 field_C; /* PS2 +0xC */
    u8 opaque_10[4];
    u32 field_14; /* PS2 +0x14 */
} Recovered_Vtable_003E12B0;
typedef char assert_Recovered_Vtable_003E12B0_C[(((int)&((Recovered_Vtable_003E12B0 *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E12B0_14[(((int)&((Recovered_Vtable_003E12B0 *)0)->field_14) == 20) ? 1 : -1];
#endif
