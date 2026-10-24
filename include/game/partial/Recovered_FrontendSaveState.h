/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_FRONTENDSAVESTATE_H
#define RECOVERED_FRONTENDSAVESTATE_H
#include "ps2/prelude.h"

typedef struct Recovered_FrontendSaveState {
    u8 opaque_0[12];
    u32 field_C; /* PS2 +0xC */
    s32 field_10; /* PS2 +0x10 */
    s32 field_14; /* PS2 +0x14 */
    s32 field_18; /* PS2 +0x18 */
    s32 field_1C; /* PS2 +0x1C */
    s32 field_20; /* PS2 +0x20 */
    s32 field_24; /* PS2 +0x24 */
    u8 opaque_28[4];
    s32 field_2C; /* PS2 +0x2C */
    s32 field_30; /* PS2 +0x30 */
    s32 field_34; /* PS2 +0x34 */
    s64 field_38; /* PS2 +0x38 */
    u8 opaque_40[1204];
    s32 field_4F4; /* PS2 +0x4F4 */
    u32 field_4F8; /* PS2 +0x4F8 */
    u8 opaque_4FC[4];
    s32 field_500; /* PS2 +0x500 */
    f32 field_504; /* PS2 +0x504 */
    u8 opaque_508[11];
    u8 field_513; /* PS2 +0x513 */
    u8 opaque_514[1];
    u8 field_515; /* PS2 +0x515 */
    u8 opaque_516[1534];
    s32 field_B14; /* PS2 +0xB14 */
    s32 field_B18; /* PS2 +0xB18 */
    u8 opaque_B1C[28];
    s32 field_B38; /* PS2 +0xB38 */
    s32 field_B3C; /* PS2 +0xB3C */
} Recovered_FrontendSaveState;
typedef char assert_Recovered_FrontendSaveState_C[(((int)&((Recovered_FrontendSaveState *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_10[(((int)&((Recovered_FrontendSaveState *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_14[(((int)&((Recovered_FrontendSaveState *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_18[(((int)&((Recovered_FrontendSaveState *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_1C[(((int)&((Recovered_FrontendSaveState *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_20[(((int)&((Recovered_FrontendSaveState *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_24[(((int)&((Recovered_FrontendSaveState *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_2C[(((int)&((Recovered_FrontendSaveState *)0)->field_2C) == 44) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_30[(((int)&((Recovered_FrontendSaveState *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_34[(((int)&((Recovered_FrontendSaveState *)0)->field_34) == 52) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_38[(((int)&((Recovered_FrontendSaveState *)0)->field_38) == 56) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_4F4[(((int)&((Recovered_FrontendSaveState *)0)->field_4F4) == 1268) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_4F8[(((int)&((Recovered_FrontendSaveState *)0)->field_4F8) == 1272) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_500[(((int)&((Recovered_FrontendSaveState *)0)->field_500) == 1280) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_504[(((int)&((Recovered_FrontendSaveState *)0)->field_504) == 1284) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_513[(((int)&((Recovered_FrontendSaveState *)0)->field_513) == 1299) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_515[(((int)&((Recovered_FrontendSaveState *)0)->field_515) == 1301) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_B14[(((int)&((Recovered_FrontendSaveState *)0)->field_B14) == 2836) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_B18[(((int)&((Recovered_FrontendSaveState *)0)->field_B18) == 2840) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_B38[(((int)&((Recovered_FrontendSaveState *)0)->field_B38) == 2872) ? 1 : -1];
typedef char assert_Recovered_FrontendSaveState_B3C[(((int)&((Recovered_FrontendSaveState *)0)->field_B3C) == 2876) ? 1 : -1];
#endif
