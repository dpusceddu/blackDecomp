/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DC240_H
#define RECOVERED_VTABLE_003DC240_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DC240 {
    u8 opaque_0[80];
    f32 field_50; /* PS2 +0x50 */
    u8 opaque_54[4];
    s8 field_58; /* PS2 +0x58 */
    u8 field_59; /* PS2 +0x59 */
} Recovered_Vtable_003DC240;
typedef char assert_Recovered_Vtable_003DC240_50[(((int)&((Recovered_Vtable_003DC240 *)0)->field_50) == 80) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC240_58[(((int)&((Recovered_Vtable_003DC240 *)0)->field_58) == 88) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC240_59[(((int)&((Recovered_Vtable_003DC240 *)0)->field_59) == 89) ? 1 : -1];
#endif
