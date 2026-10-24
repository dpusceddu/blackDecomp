/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003E0958_H
#define RECOVERED_VTABLE_003E0958_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003E0958 {
    u8 opaque_0[16];
    s16 field_10; /* PS2 +0x10 */
    s8 field_12; /* PS2 +0x12 */
    u8 opaque_13[5];
    s32 field_18; /* PS2 +0x18 */
    s32 field_1C; /* PS2 +0x1C */
    s32 field_20; /* PS2 +0x20 */
    u8 opaque_24[308];
    f32 field_158; /* PS2 +0x158 */
    u8 opaque_15C[4];
    s32 field_160; /* PS2 +0x160 */
} Recovered_Vtable_003E0958;
typedef char assert_Recovered_Vtable_003E0958_10[(((int)&((Recovered_Vtable_003E0958 *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E0958_12[(((int)&((Recovered_Vtable_003E0958 *)0)->field_12) == 18) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E0958_18[(((int)&((Recovered_Vtable_003E0958 *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E0958_1C[(((int)&((Recovered_Vtable_003E0958 *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E0958_20[(((int)&((Recovered_Vtable_003E0958 *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E0958_158[(((int)&((Recovered_Vtable_003E0958 *)0)->field_158) == 344) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E0958_160[(((int)&((Recovered_Vtable_003E0958 *)0)->field_160) == 352) ? 1 : -1];
#endif
