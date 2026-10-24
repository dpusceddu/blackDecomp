/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_ROOMREGION_H
#define RECOVERED_ROOMREGION_H
#include "ps2/prelude.h"

typedef struct Recovered_RoomRegion {
    u8 opaque_0[304];
    s128 field_130; /* PS2 +0x130 */
    s128 field_140; /* PS2 +0x140 */
} Recovered_RoomRegion;
typedef char assert_Recovered_RoomRegion_130[(((int)&((Recovered_RoomRegion *)0)->field_130) == 304) ? 1 : -1];
typedef char assert_Recovered_RoomRegion_140[(((int)&((Recovered_RoomRegion *)0)->field_140) == 320) ? 1 : -1];
#endif
