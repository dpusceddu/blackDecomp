/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PHYSICSRELOCATIONCONTEXT_H
#define RECOVERED_PHYSICSRELOCATIONCONTEXT_H
#include "ps2/prelude.h"

typedef struct Recovered_PhysicsRelocationContext {
    u8 opaque_0[8];
    s32 field_8; /* PS2 +0x8 */
} Recovered_PhysicsRelocationContext;
typedef char assert_Recovered_PhysicsRelocationContext_8[(((int)&((Recovered_PhysicsRelocationContext *)0)->field_8) == 8) ? 1 : -1];
#endif
