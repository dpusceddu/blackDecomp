/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_COLLISIONPAIRPS2_H
#define RECOVERED_COLLISIONPAIRPS2_H
#include "ps2/prelude.h"

typedef struct Recovered_CollisionPairPS2 {
    void * field_0; /* PS2 +0x0 */
    void * field_4; /* PS2 +0x4 */
} Recovered_CollisionPairPS2;
typedef char assert_Recovered_CollisionPairPS2_0[(((int)&((Recovered_CollisionPairPS2 *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_CollisionPairPS2_4[(((int)&((Recovered_CollisionPairPS2 *)0)->field_4) == 4) ? 1 : -1];
#endif
