/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_FORMATIONGOAL_H
#define RECOVERED_FORMATIONGOAL_H
#include "ps2/prelude.h"

typedef struct Recovered_FormationGoal {
    u8 opaque_0[16];
    s32 field_10; /* PS2 +0x10 */
    u8 opaque_14[12];
    u128 field_20; /* PS2 +0x20 */
    s32 field_30; /* PS2 +0x30 */
} Recovered_FormationGoal;
typedef char assert_Recovered_FormationGoal_10[(((int)&((Recovered_FormationGoal *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_FormationGoal_20[(((int)&((Recovered_FormationGoal *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_FormationGoal_30[(((int)&((Recovered_FormationGoal *)0)->field_30) == 48) ? 1 : -1];
#endif
