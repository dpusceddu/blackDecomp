/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PHYSICSSCENESETTINGS_H
#define RECOVERED_PHYSICSSCENESETTINGS_H
#include "ps2/prelude.h"

typedef struct Recovered_PhysicsSceneSettings {
    u128 field_0; /* PS2 +0x0 */
    u8 opaque_10[16];
    f32 field_20; /* PS2 +0x20 */
    s32 field_24; /* PS2 +0x24 */
    s32 field_28; /* PS2 +0x28 */
    s32 field_2C; /* PS2 +0x2C */
    s32 field_30; /* PS2 +0x30 */
    s32 field_34; /* PS2 +0x34 */
    s32 field_38; /* PS2 +0x38 */
} Recovered_PhysicsSceneSettings;
typedef char assert_Recovered_PhysicsSceneSettings_0[(((int)&((Recovered_PhysicsSceneSettings *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_PhysicsSceneSettings_20[(((int)&((Recovered_PhysicsSceneSettings *)0)->field_20) == 32) ? 1 : -1];
typedef char assert_Recovered_PhysicsSceneSettings_24[(((int)&((Recovered_PhysicsSceneSettings *)0)->field_24) == 36) ? 1 : -1];
typedef char assert_Recovered_PhysicsSceneSettings_28[(((int)&((Recovered_PhysicsSceneSettings *)0)->field_28) == 40) ? 1 : -1];
typedef char assert_Recovered_PhysicsSceneSettings_2C[(((int)&((Recovered_PhysicsSceneSettings *)0)->field_2C) == 44) ? 1 : -1];
typedef char assert_Recovered_PhysicsSceneSettings_30[(((int)&((Recovered_PhysicsSceneSettings *)0)->field_30) == 48) ? 1 : -1];
typedef char assert_Recovered_PhysicsSceneSettings_34[(((int)&((Recovered_PhysicsSceneSettings *)0)->field_34) == 52) ? 1 : -1];
typedef char assert_Recovered_PhysicsSceneSettings_38[(((int)&((Recovered_PhysicsSceneSettings *)0)->field_38) == 56) ? 1 : -1];
#endif
