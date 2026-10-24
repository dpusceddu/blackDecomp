/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PS2COLLISIONQUEUE_H
#define RECOVERED_PS2COLLISIONQUEUE_H
#include "ps2/prelude.h"

typedef struct Recovered_PS2CollisionQueue {
    void * field_0; /* PS2 +0x0 */
    void * field_4; /* PS2 +0x4 */
    void * field_8; /* PS2 +0x8 */
    void * field_C; /* PS2 +0xC */
    void * field_10; /* PS2 +0x10 */
    void * field_14; /* PS2 +0x14 */
    void * field_18; /* PS2 +0x18 */
    void * field_1C; /* PS2 +0x1C */
} Recovered_PS2CollisionQueue;
typedef char assert_Recovered_PS2CollisionQueue_0[(((int)&((Recovered_PS2CollisionQueue *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_PS2CollisionQueue_4[(((int)&((Recovered_PS2CollisionQueue *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_PS2CollisionQueue_8[(((int)&((Recovered_PS2CollisionQueue *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_PS2CollisionQueue_C[(((int)&((Recovered_PS2CollisionQueue *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_PS2CollisionQueue_10[(((int)&((Recovered_PS2CollisionQueue *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_PS2CollisionQueue_14[(((int)&((Recovered_PS2CollisionQueue *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_PS2CollisionQueue_18[(((int)&((Recovered_PS2CollisionQueue *)0)->field_18) == 24) ? 1 : -1];
typedef char assert_Recovered_PS2CollisionQueue_1C[(((int)&((Recovered_PS2CollisionQueue *)0)->field_1C) == 28) ? 1 : -1];
#endif
