/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PHYSICSSTORAGEREQUIREMENT_H
#define RECOVERED_PHYSICSSTORAGEREQUIREMENT_H
#include "ps2/prelude.h"

typedef struct Recovered_PhysicsStorageRequirement {
    u32 field_0; /* PS2 +0x0 */
    u32 field_4; /* PS2 +0x4 */
} Recovered_PhysicsStorageRequirement;
typedef char assert_Recovered_PhysicsStorageRequirement_0[(((int)&((Recovered_PhysicsStorageRequirement *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_PhysicsStorageRequirement_4[(((int)&((Recovered_PhysicsStorageRequirement *)0)->field_4) == 4) ? 1 : -1];
#endif
