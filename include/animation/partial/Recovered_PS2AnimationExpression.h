/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PS2ANIMATIONEXPRESSION_H
#define RECOVERED_PS2ANIMATIONEXPRESSION_H
#include "ps2/prelude.h"

typedef struct Recovered_PS2AnimationExpression {
    u8 field_0; /* PS2 +0x0 */
    s8 field_1; /* PS2 +0x1 */
    s16 field_2; /* PS2 +0x2 */
    u8 opaque_4[4];
    void * field_8; /* PS2 +0x8 */
} Recovered_PS2AnimationExpression;
typedef char assert_Recovered_PS2AnimationExpression_0[(((int)&((Recovered_PS2AnimationExpression *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_PS2AnimationExpression_1[(((int)&((Recovered_PS2AnimationExpression *)0)->field_1) == 1) ? 1 : -1];
typedef char assert_Recovered_PS2AnimationExpression_2[(((int)&((Recovered_PS2AnimationExpression *)0)->field_2) == 2) ? 1 : -1];
typedef char assert_Recovered_PS2AnimationExpression_8[(((int)&((Recovered_PS2AnimationExpression *)0)->field_8) == 8) ? 1 : -1];
#endif
