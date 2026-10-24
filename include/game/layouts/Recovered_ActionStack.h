/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ACTIONSTACK_H
#define RECOVERED_ACTIONSTACK_H
#include "ps2/prelude.h"

typedef struct Recovered_ActionStack {
    s32 field_0; /* PS2 +0x0 */
    s32 field_4; /* PS2 +0x4 */
    s32 field_8; /* PS2 +0x8 */
    s32 field_C; /* PS2 +0xC */
    s32 field_10; /* PS2 +0x10 */
    s32 field_14; /* PS2 +0x14 */
    s32 field_18; /* PS2 +0x18 */
    s32 field_1C; /* PS2 +0x1C */
    u8 opaque_20[1184];
    s32 field_4C0; /* PS2 +0x4C0 */
    u8 opaque_4C4[588];
    s32 field_710; /* PS2 +0x710 */
    s32 field_714; /* PS2 +0x714 */
} Recovered_ActionStack;
typedef char assert_Recovered_ActionStack_0[(((int)&((Recovered_ActionStack *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_ActionStack_4[(((int)&((Recovered_ActionStack *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_ActionStack_8[(((int)&((Recovered_ActionStack *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_ActionStack_C[(((int)&((Recovered_ActionStack *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_ActionStack_10[(((int)&((Recovered_ActionStack *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_ActionStack_14[(((int)&((Recovered_ActionStack *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_ActionStack_18[(((int)&((Recovered_ActionStack *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_ActionStack_1C[(((int)&((Recovered_ActionStack *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_ActionStack_4C0[(((int)&((Recovered_ActionStack *)0)->field_4C0) == 1216) ? 1 : -1];
typedef char assert_Recovered_ActionStack_710[(((int)&((Recovered_ActionStack *)0)->field_710) == 1808) ? 1 : -1];
typedef char assert_Recovered_ActionStack_714[(((int)&((Recovered_ActionStack *)0)->field_714) == 1812) ? 1 : -1];
#endif
