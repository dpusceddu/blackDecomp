/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_COLLISIONWORKPS2_H
#define RECOVERED_COLLISIONWORKPS2_H
#include "ps2/prelude.h"

typedef struct Recovered_CollisionWorkPS2 {
    void * field_0; /* PS2 +0x0 */
    s32 field_4; /* PS2 +0x4 */
    u8 opaque_8[4];
    void * field_C; /* PS2 +0xC */
    s32 field_10; /* PS2 +0x10 */
    u8 opaque_14[4];
    s32 field_18; /* PS2 +0x18 */
    void * field_1C; /* PS2 +0x1C */
} Recovered_CollisionWorkPS2;
typedef char assert_Recovered_CollisionWorkPS2_0[(((int)&((Recovered_CollisionWorkPS2 *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_CollisionWorkPS2_4[(((int)&((Recovered_CollisionWorkPS2 *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_CollisionWorkPS2_C[(((int)&((Recovered_CollisionWorkPS2 *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_CollisionWorkPS2_10[(((int)&((Recovered_CollisionWorkPS2 *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_CollisionWorkPS2_18[(((int)&((Recovered_CollisionWorkPS2 *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_CollisionWorkPS2_1C[(((int)&((Recovered_CollisionWorkPS2 *)0)->field_1C) == 28) ? 1 : -1];
#endif
