/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DB078_H
#define RECOVERED_VTABLE_003DB078_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DB078 {
    u8 opaque_0[4];
    void * field_4; /* PS2 +0x4 */
    u8 opaque_8[4];
    u8 field_C; /* PS2 +0xC */
    u8 opaque_D[3];
    u128 field_10; /* PS2 +0x10 */
    void * field_20; /* PS2 +0x20 */
} Recovered_Vtable_003DB078;
typedef char assert_Recovered_Vtable_003DB078_4[(((int)&((Recovered_Vtable_003DB078 *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB078_C[(((int)&((Recovered_Vtable_003DB078 *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB078_10[(((int)&((Recovered_Vtable_003DB078 *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DB078_20[(((int)&((Recovered_Vtable_003DB078 *)0)->field_20) == 32) ? 1 : -1];
#endif
