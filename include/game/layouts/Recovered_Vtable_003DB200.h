/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DB200_H
#define RECOVERED_VTABLE_003DB200_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DB200 {
    u8 opaque_0[8];
    f32 field_8; /* PS2 +0x8 */
    f32 field_C; /* PS2 +0xC */
    s32 field_10; /* PS2 +0x10 */
    s32 field_14; /* PS2 +0x14 */
    s32 field_18; /* PS2 +0x18 */
} Recovered_Vtable_003DB200;
typedef char assert_Recovered_Vtable_003DB200_8[(((int)&((Recovered_Vtable_003DB200 *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB200_C[(((int)&((Recovered_Vtable_003DB200 *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB200_10[(((int)&((Recovered_Vtable_003DB200 *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB200_14[(((int)&((Recovered_Vtable_003DB200 *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB200_18[(((int)&((Recovered_Vtable_003DB200 *)0)->field_18) == 24) ? 1 : -1];
#endif
