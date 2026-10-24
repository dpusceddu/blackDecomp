/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DC270_H
#define RECOVERED_VTABLE_003DC270_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DC270 {
    u8 opaque_0[76];
    s32 field_4C; /* PS2 +0x4C */
    u8 opaque_50[44];
    void * field_7C; /* PS2 +0x7C */
    u8 opaque_80[7964];
    s32 field_1F9C; /* PS2 +0x1F9C */
    f32 field_1FA0; /* PS2 +0x1FA0 */
    u8 opaque_1FA4[12];
    u128 field_1FB0; /* PS2 +0x1FB0 */
    u8 field_1FC0; /* PS2 +0x1FC0 */
} Recovered_Vtable_003DC270;
typedef char assert_Recovered_Vtable_003DC270_4C[(((int)&((Recovered_Vtable_003DC270 *)0)->field_4C) == 76) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC270_7C[(((int)&((Recovered_Vtable_003DC270 *)0)->field_7C) == 124) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC270_1F9C[(((int)&((Recovered_Vtable_003DC270 *)0)->field_1F9C) == 8092) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC270_1FA0[(((int)&((Recovered_Vtable_003DC270 *)0)->field_1FA0) == 8096) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC270_1FB0[(((int)&((Recovered_Vtable_003DC270 *)0)->field_1FB0) == 8112) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DC270_1FC0[(((int)&((Recovered_Vtable_003DC270 *)0)->field_1FC0) == 8128) ? 1 : -1];
#endif
