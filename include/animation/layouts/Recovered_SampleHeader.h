/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_SAMPLEHEADER_H
#define RECOVERED_SAMPLEHEADER_H
#include "ps2/prelude.h"

typedef struct Recovered_SampleHeader {
    s128 field_0; /* PS2 +0x0 */
    u8 opaque_10[16];
} Recovered_SampleHeader;
typedef char assert_Recovered_SampleHeader_0[(((int)&((Recovered_SampleHeader *)0)->field_0) == 0) ? 1 : -1];
#endif
