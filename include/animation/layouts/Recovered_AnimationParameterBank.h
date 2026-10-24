/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ANIMATIONPARAMETERBANK_H
#define RECOVERED_ANIMATIONPARAMETERBANK_H
#include "ps2/prelude.h"

typedef struct Recovered_AnimationParameterBank {
    u8 opaque_0[280];
    s32 field_118; /* PS2 +0x118 */
} Recovered_AnimationParameterBank;
typedef char assert_Recovered_AnimationParameterBank_118[(((int)&((Recovered_AnimationParameterBank *)0)->field_118) == 280) ? 1 : -1];
#endif
