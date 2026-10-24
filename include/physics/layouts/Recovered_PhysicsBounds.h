/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PHYSICSBOUNDS_H
#define RECOVERED_PHYSICSBOUNDS_H
#include "ps2/prelude.h"

typedef struct Recovered_PhysicsBounds {
    s128 field_0; /* PS2 +0x0 */
    s128 field_10; /* PS2 +0x10 */
} Recovered_PhysicsBounds;
typedef char assert_Recovered_PhysicsBounds_0[(((int)&((Recovered_PhysicsBounds *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_PhysicsBounds_10[(((int)&((Recovered_PhysicsBounds *)0)->field_10) == 16) ? 1 : -1];
#endif
