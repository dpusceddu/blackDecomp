/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DC208_H
#define RECOVERED_VTABLE_003DC208_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DC208 {
    u8 opaque_0[28];
    u8 field_1C; /* PS2 +0x1C */
    u8 opaque_1D[3];
    void * field_20; /* PS2 +0x20 */
    u8 opaque_24[8];
    s32 field_2C; /* PS2 +0x2C */
} Recovered_Vtable_003DC208;
typedef char assert_Recovered_Vtable_003DC208_1C[(((int)&((Recovered_Vtable_003DC208 *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC208_20[(((int)&((Recovered_Vtable_003DC208 *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC208_2C[(((int)&((Recovered_Vtable_003DC208 *)0)->field_2C) == 44) ? 1 : -1];
#endif
