/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DB3C0_H
#define RECOVERED_VTABLE_003DB3C0_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DB3C0 {
    s32 field_0; /* PS2 +0x0 */
    u8 opaque_4[20];
    s32 field_18; /* PS2 +0x18 */
    u8 opaque_1C[128];
    u8 field_9C; /* PS2 +0x9C */
    u8 field_9D; /* PS2 +0x9D */
    u8 opaque_9E[2];
    u32 field_A0; /* PS2 +0xA0 */
} Recovered_Vtable_003DB3C0;
typedef char assert_Recovered_Vtable_003DB3C0_0[(((int)&((Recovered_Vtable_003DB3C0 *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB3C0_18[(((int)&((Recovered_Vtable_003DB3C0 *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB3C0_9C[(((int)&((Recovered_Vtable_003DB3C0 *)0)->field_9C) == 156) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB3C0_9D[(((int)&((Recovered_Vtable_003DB3C0 *)0)->field_9D) == 157) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB3C0_A0[(((int)&((Recovered_Vtable_003DB3C0 *)0)->field_A0) == 160) ? 1 : -1];
#endif
