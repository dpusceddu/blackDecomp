/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_VTABLE_003DBE70_H
#define RECOVERED_VTABLE_003DBE70_H
#include "ps2/prelude.h"

typedef struct Recovered_Vtable_003DBE70 {
    u8 opaque_0[16];
    void * field_10; /* PS2 +0x10 */
    u8 opaque_14[12];
    void * field_20; /* PS2 +0x20 */
    u8 opaque_24[44];
    s128 field_50; /* PS2 +0x50 */
    s128 field_60; /* PS2 +0x60 */
} Recovered_Vtable_003DBE70;
typedef char assert_Recovered_Vtable_003DBE70_10[(((int)&((Recovered_Vtable_003DBE70 *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DBE70_20[(((int)&((Recovered_Vtable_003DBE70 *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DBE70_50[(((int)&((Recovered_Vtable_003DBE70 *)0)->field_50) == 80) ? 1 : -1];
typedef char assert_Recovered_Vtable_003DBE70_60[(((int)&((Recovered_Vtable_003DBE70 *)0)->field_60) == 96) ? 1 : -1];
#endif
