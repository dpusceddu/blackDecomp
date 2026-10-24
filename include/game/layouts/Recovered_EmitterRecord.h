/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_EMITTERRECORD_H
#define RECOVERED_EMITTERRECORD_H
#include "ps2/prelude.h"

typedef struct Recovered_EmitterRecord {
    u8 opaque_0[168];
    u32 field_A8; /* PS2 +0xA8 */
} Recovered_EmitterRecord;
typedef char assert_Recovered_EmitterRecord_A8[(((int)&((Recovered_EmitterRecord *)0)->field_A8) == 168) ? 1 : -1];
#endif
