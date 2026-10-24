/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ANIMATIONPARAMETERS_H
#define RECOVERED_ANIMATIONPARAMETERS_H
#include "ps2/prelude.h"

typedef struct Recovered_AnimationParameters {
    u8 opaque_0[280];
    s32 field_118; /* PS2 +0x118 */
} Recovered_AnimationParameters;
typedef char assert_Recovered_AnimationParameters_118[(((int)&((Recovered_AnimationParameters *)0)->field_118) == 280) ? 1 : -1];
#endif
