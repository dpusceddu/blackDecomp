/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RENDERABLESTATE_H
#define RECOVERED_RENDERABLESTATE_H
#include "ps2/prelude.h"

typedef struct Recovered_RenderableState {
    u8 opaque_0[16];
    void * field_10; /* PS2 +0x10 */
    u8 opaque_14[160];
    s32 field_B4; /* PS2 +0xB4 */
    u8 opaque_B8[12];
    u32 field_C4; /* PS2 +0xC4 */
    u8 opaque_C8[72];
    u32 field_110; /* PS2 +0x110 */
    u32 field_114; /* PS2 +0x114 */
    u32 field_118; /* PS2 +0x118 */
    u8 opaque_11C[30];
    u8 field_13A; /* PS2 +0x13A */
    u8 opaque_13B[1];
    u8 field_13C; /* PS2 +0x13C */
    u8 opaque_13D[3];
    u32 field_140; /* PS2 +0x140 */
    u8 opaque_144[12];
    u16 field_150; /* PS2 +0x150 */
    u8 field_152; /* PS2 +0x152 */
    u8 field_153; /* PS2 +0x153 */
    u8 field_154; /* PS2 +0x154 */
    u8 field_155; /* PS2 +0x155 */
    u8 opaque_156[2];
    void * field_158; /* PS2 +0x158 */
} Recovered_RenderableState;
typedef char assert_Recovered_RenderableState_10[(((int)&((Recovered_RenderableState *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_RenderableState_B4[(((int)&((Recovered_RenderableState *)0)->field_B4) == 180) ? 1 : -1];
typedef char assert_Recovered_RenderableState_C4[(((int)&((Recovered_RenderableState *)0)->field_C4) == 196) ? 1 : -1];
typedef char assert_Recovered_RenderableState_110[(((int)&((Recovered_RenderableState *)0)->field_110) == 272) ? 1 : -1];
typedef char assert_Recovered_RenderableState_114[(((int)&((Recovered_RenderableState *)0)->field_114) == 276) ? 1 : -1];
typedef char assert_Recovered_RenderableState_118[(((int)&((Recovered_RenderableState *)0)->field_118) == 280) ? 1 : -1];
typedef char assert_Recovered_RenderableState_13A[(((int)&((Recovered_RenderableState *)0)->field_13A) == 314) ? 1 : -1];
typedef char assert_Recovered_RenderableState_13C[(((int)&((Recovered_RenderableState *)0)->field_13C) == 316) ? 1 : -1];
typedef char assert_Recovered_RenderableState_140[(((int)&((Recovered_RenderableState *)0)->field_140) == 320) ? 1 : -1];
typedef char assert_Recovered_RenderableState_150[(((int)&((Recovered_RenderableState *)0)->field_150) == 336) ? 1 : -1];
typedef char assert_Recovered_RenderableState_152[(((int)&((Recovered_RenderableState *)0)->field_152) == 338) ? 1 : -1];
typedef char assert_Recovered_RenderableState_153[(((int)&((Recovered_RenderableState *)0)->field_153) == 339) ? 1 : -1];
typedef char assert_Recovered_RenderableState_154[(((int)&((Recovered_RenderableState *)0)->field_154) == 340) ? 1 : -1];
typedef char assert_Recovered_RenderableState_155[(((int)&((Recovered_RenderableState *)0)->field_155) == 341) ? 1 : -1];
typedef char assert_Recovered_RenderableState_158[(((int)&((Recovered_RenderableState *)0)->field_158) == 344) ? 1 : -1];
#endif
