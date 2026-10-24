/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003E1260_H
#define RECOVERED_VTABLE_003E1260_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003E1260 {
    u8 opaque_0[8];
    s32 field_8; /* PS2 +0x8 */
    s32 field_C; /* PS2 +0xC */
    u8 opaque_10[4];
    u32 field_14; /* PS2 +0x14 */
    u8 opaque_18[20];
    s32 field_2C; /* PS2 +0x2C */
} Recovered_Vtable_003E1260;
typedef char assert_Recovered_Vtable_003E1260_8[(((int)&((Recovered_Vtable_003E1260 *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E1260_C[(((int)&((Recovered_Vtable_003E1260 *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E1260_14[(((int)&((Recovered_Vtable_003E1260 *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_Vtable_003E1260_2C[(((int)&((Recovered_Vtable_003E1260 *)0)->field_2C) == 44) ? 1 : -1];
#endif
