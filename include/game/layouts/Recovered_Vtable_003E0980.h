/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003E0980_H
#define RECOVERED_VTABLE_003E0980_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003E0980 {
    u8 opaque_0[16];
    s16 field_10; /* PS2 +0x10 */
    s8 field_12; /* PS2 +0x12 */
    u8 opaque_13[85];
    s32 field_68; /* PS2 +0x68 */
    s32 field_6C; /* PS2 +0x6C */
} Recovered_Vtable_003E0980;
typedef char assert_Recovered_Vtable_003E0980_10[(((int)&((Recovered_Vtable_003E0980 *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E0980_12[(((int)&((Recovered_Vtable_003E0980 *)0)->field_12) == 18) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E0980_68[(((int)&((Recovered_Vtable_003E0980 *)0)->field_68) == 104) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E0980_6C[(((int)&((Recovered_Vtable_003E0980 *)0)->field_6C) == 108) ? 1 : -1];
#endif
