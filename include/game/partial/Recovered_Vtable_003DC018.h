/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DC018_H
#define RECOVERED_VTABLE_003DC018_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DC018 {
    s64 field_0; /* PS2 +0x0 */
    u8 opaque_8[8];
    void * field_10; /* PS2 +0x10 */
    u8 opaque_14[265];
    u8 field_11D; /* PS2 +0x11D */
    u8 opaque_11E[2];
    s32 field_120; /* PS2 +0x120 */
    s32 field_124; /* PS2 +0x124 */
} Recovered_Vtable_003DC018;
typedef char assert_Recovered_Vtable_003DC018_0[(((int)&((Recovered_Vtable_003DC018 *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC018_10[(((int)&((Recovered_Vtable_003DC018 *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC018_11D[(((int)&((Recovered_Vtable_003DC018 *)0)->field_11D) == 285) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC018_120[(((int)&((Recovered_Vtable_003DC018 *)0)->field_120) == 288) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC018_124[(((int)&((Recovered_Vtable_003DC018 *)0)->field_124) == 292) ? 1 : -1];
#endif
