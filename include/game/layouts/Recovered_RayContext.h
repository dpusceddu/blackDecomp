/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RAYCONTEXT_H
#define RECOVERED_RAYCONTEXT_H
#include "ps2/prelude.h"

typedef struct Recovered_RayContext {
    s128 field_0; /* PS2 +0x0 */
    s128 field_10; /* PS2 +0x10 */
    s32 field_20; /* PS2 +0x20 */
    s32 field_24; /* PS2 +0x24 */
    u8 field_28; /* PS2 +0x28 */
    u8 field_29; /* PS2 +0x29 */
    u8 opaque_2A[6];
    u128 field_30; /* PS2 +0x30 */
    u128 field_40; /* PS2 +0x40 */
    u8 opaque_50[16];
    u128 field_60; /* PS2 +0x60 */
    u8 opaque_70[4];
    s32 field_74; /* PS2 +0x74 */
    f32 field_78; /* PS2 +0x78 */
    f32 field_7C; /* PS2 +0x7C */
    s128 field_80; /* PS2 +0x80 */
    s8 field_90; /* PS2 +0x90 */
} Recovered_RayContext;
typedef char assert_Recovered_RayContext_0[(((int)&((Recovered_RayContext *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_RayContext_10[(((int)&((Recovered_RayContext *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_RayContext_20[(((int)&((Recovered_RayContext *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_RayContext_24[(((int)&((Recovered_RayContext *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_RayContext_28[(((int)&((Recovered_RayContext *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_RayContext_29[(((int)&((Recovered_RayContext *)0)->field_29) == 41) ? 1 : -1];
typedef char assert_Recovered_RayContext_30[(((int)&((Recovered_RayContext *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_RayContext_40[(((int)&((Recovered_RayContext *)0)->field_40) == 64) ? 1 : -1];
typedef char assert_Recovered_RayContext_60[(((int)&((Recovered_RayContext *)0)->field_60) == 96) ? 1 : -1];
typedef char assert_Recovered_RayContext_74[(((int)&((Recovered_RayContext *)0)->field_74) == 116) ? 1 : -1];
typedef char assert_Recovered_RayContext_78[(((int)&((Recovered_RayContext *)0)->field_78) == 120) ? 1 : -1];
typedef char assert_Recovered_RayContext_7C[(((int)&((Recovered_RayContext *)0)->field_7C) == 124) ? 1 : -1];
typedef char assert_Recovered_RayContext_80[(((int)&((Recovered_RayContext *)0)->field_80) == 128) ? 1 : -1];
typedef char assert_Recovered_RayContext_90[(((int)&((Recovered_RayContext *)0)->field_90) == 144) ? 1 : -1];
#endif
