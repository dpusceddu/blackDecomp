/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ANIMATIONGRAPHNODE_H
#define RECOVERED_ANIMATIONGRAPHNODE_H
#include "ps2/prelude.h"

typedef struct Recovered_AnimationGraphNode {
    u8 field_0; /* PS2 +0x0 */
    s8 field_1; /* PS2 +0x1 */
    s16 field_2; /* PS2 +0x2 */
    f32 field_4; /* PS2 +0x4 */
    void * field_8; /* PS2 +0x8 */
    u8 opaque_C[4];
    void * field_10; /* PS2 +0x10 */
    void * field_14; /* PS2 +0x14 */
    void * field_18; /* PS2 +0x18 */
    void * field_1C; /* PS2 +0x1C */
    void * field_20; /* PS2 +0x20 */
    void * field_24; /* PS2 +0x24 */
    void * field_28; /* PS2 +0x28 */
    void * field_2C; /* PS2 +0x2C */
    s32 field_30; /* PS2 +0x30 */
} Recovered_AnimationGraphNode;
typedef char assert_Recovered_AnimationGraphNode_0[(((int)&((Recovered_AnimationGraphNode *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_AnimationGraphNode_1[(((int)&((Recovered_AnimationGraphNode *)0)->field_1) == 1) ? 1 : -1];
typedef char assert_Recovered_AnimationGraphNode_2[(((int)&((Recovered_AnimationGraphNode *)0)->field_2) == 2) ? 1 : -1];
typedef char assert_Recovered_AnimationGraphNode_4[(((int)&((Recovered_AnimationGraphNode *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_AnimationGraphNode_8[(((int)&((Recovered_AnimationGraphNode *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_AnimationGraphNode_10[(((int)&((Recovered_AnimationGraphNode *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_AnimationGraphNode_14[(((int)&((Recovered_AnimationGraphNode *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_AnimationGraphNode_18[(((int)&((Recovered_AnimationGraphNode *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_AnimationGraphNode_1C[(((int)&((Recovered_AnimationGraphNode *)0)->field_1C) == 28) ? 1 : -1];
typedef char assert_Recovered_AnimationGraphNode_20[(((int)&((Recovered_AnimationGraphNode *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_AnimationGraphNode_24[(((int)&((Recovered_AnimationGraphNode *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_AnimationGraphNode_28[(((int)&((Recovered_AnimationGraphNode *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_AnimationGraphNode_2C[(((int)&((Recovered_AnimationGraphNode *)0)->field_2C) == 44) ? 1 : -1];
typedef char assert_Recovered_AnimationGraphNode_30[(((int)&((Recovered_AnimationGraphNode *)0)->field_30) == 48) ? 1 : -1];
#endif
