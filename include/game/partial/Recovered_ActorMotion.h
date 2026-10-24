/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ACTORMOTION_H
#define RECOVERED_ACTORMOTION_H
#include "ps2/prelude.h"

typedef struct Recovered_ActorMotion {
    u128 field_0; /* PS2 +0x0 */
    u128 field_10; /* PS2 +0x10 */
    u128 field_20; /* PS2 +0x20 */
    u128 field_30; /* PS2 +0x30 */
} Recovered_ActorMotion;
typedef char assert_Recovered_ActorMotion_0[(((int)&((Recovered_ActorMotion *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_ActorMotion_10[(((int)&((Recovered_ActorMotion *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_ActorMotion_20[(((int)&((Recovered_ActorMotion *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_ActorMotion_30[(((int)&((Recovered_ActorMotion *)0)->field_30) == 48) ? 1 : -1];
#endif
