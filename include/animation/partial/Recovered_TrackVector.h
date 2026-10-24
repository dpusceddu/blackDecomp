/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_TRACKVECTOR_H
#define RECOVERED_TRACKVECTOR_H
#include "ps2/prelude.h"

typedef struct Recovered_TrackVector {
    u8 opaque_0[4];
    f32 field_4; /* PS2 +0x4 */
    f32 field_8; /* PS2 +0x8 */
    f32 field_C; /* PS2 +0xC */
} Recovered_TrackVector;
typedef char assert_Recovered_TrackVector_4[(((int)&((Recovered_TrackVector *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_TrackVector_8[(((int)&((Recovered_TrackVector *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_TrackVector_C[(((int)&((Recovered_TrackVector *)0)->field_C) == 12) ? 1 : -1];
#endif
