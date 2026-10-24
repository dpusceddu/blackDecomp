/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ANIMATIONCLIPINDEX_H
#define RECOVERED_ANIMATIONCLIPINDEX_H
#include "ps2/prelude.h"

typedef struct Recovered_AnimationClipIndex {
    u32 field_0; /* PS2 +0x0 */
    u32 field_4; /* PS2 +0x4 */
    void * field_8; /* PS2 +0x8 */
    u32 field_C; /* PS2 +0xC */
    u32 field_10; /* PS2 +0x10 */
} Recovered_AnimationClipIndex;
typedef char assert_Recovered_AnimationClipIndex_0[(((int)&((Recovered_AnimationClipIndex *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_AnimationClipIndex_4[(((int)&((Recovered_AnimationClipIndex *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_AnimationClipIndex_8[(((int)&((Recovered_AnimationClipIndex *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_AnimationClipIndex_C[(((int)&((Recovered_AnimationClipIndex *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_AnimationClipIndex_10[(((int)&((Recovered_AnimationClipIndex *)0)->field_10) == 16) ? 1 : -1];
#endif
