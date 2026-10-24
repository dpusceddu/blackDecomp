/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PHYSICSINSTANCE_H
#define RECOVERED_PHYSICSINSTANCE_H
#include "ps2/prelude.h"

typedef struct Recovered_PhysicsInstance {
    void * field_0; /* PS2 +0x0 */
    u8 opaque_4[12];
    s128 field_10; /* PS2 +0x10 */
    s128 field_20; /* PS2 +0x20 */
    s128 field_30; /* PS2 +0x30 */
    s128 field_40; /* PS2 +0x40 */
    void * field_50; /* PS2 +0x50 */
    u8 opaque_54[4];
    void * field_58; /* PS2 +0x58 */
    u8 opaque_5C[4];
    s32 field_60; /* PS2 +0x60 */
} Recovered_PhysicsInstance;
typedef char assert_Recovered_PhysicsInstance_0[(((int)&((Recovered_PhysicsInstance *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_PhysicsInstance_10[(((int)&((Recovered_PhysicsInstance *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_PhysicsInstance_20[(((int)&((Recovered_PhysicsInstance *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_PhysicsInstance_30[(((int)&((Recovered_PhysicsInstance *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_PhysicsInstance_40[(((int)&((Recovered_PhysicsInstance *)0)->field_40) == 64) ? 1 : -1];
typedef char assert_Recovered_PhysicsInstance_50[(((int)&((Recovered_PhysicsInstance *)0)->field_50) == 80) ? 1 : -1];
typedef char assert_Recovered_PhysicsInstance_58[(((int)&((Recovered_PhysicsInstance *)0)->field_58) == 88) ? 1 : -1];
typedef char assert_Recovered_PhysicsInstance_60[(((int)&((Recovered_PhysicsInstance *)0)->field_60) == 96) ? 1 : -1];
#endif
