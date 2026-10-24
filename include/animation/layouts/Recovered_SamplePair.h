/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_SAMPLEPAIR_H
#define RECOVERED_SAMPLEPAIR_H
#include "ps2/prelude.h"

typedef struct Recovered_SamplePair {
    s32 field_0; /* PS2 +0x0 */
    s32 field_4; /* PS2 +0x4 */
    u8 opaque_8[4];
    u8 field_C; /* PS2 +0xC */
} Recovered_SamplePair;
typedef char assert_Recovered_SamplePair_0[(((int)&((Recovered_SamplePair *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_SamplePair_4[(((int)&((Recovered_SamplePair *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_SamplePair_C[(((int)&((Recovered_SamplePair *)0)->field_C) == 12) ? 1 : -1];
#endif
