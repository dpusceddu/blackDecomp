/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DD1A0_H
#define RECOVERED_VTABLE_003DD1A0_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DD1A0 {
    u8 opaque_0[96];
    s32 field_60; /* PS2 +0x60 */
    s32 field_64; /* PS2 +0x64 */
    u8 opaque_68[20];
    s32 field_7C; /* PS2 +0x7C */
} Recovered_Vtable_003DD1A0;
typedef char assert_Recovered_Vtable_003DD1A0_60[(((int)&((Recovered_Vtable_003DD1A0 *)0)->field_60) == 96) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DD1A0_64[(((int)&((Recovered_Vtable_003DD1A0 *)0)->field_64) == 100) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DD1A0_7C[(((int)&((Recovered_Vtable_003DD1A0 *)0)->field_7C) == 124) ? 1 : -1];
#endif
