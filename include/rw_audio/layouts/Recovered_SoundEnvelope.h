/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_SOUNDENVELOPE_H
#define RECOVERED_SOUNDENVELOPE_H
#include "ps2/prelude.h"

typedef struct Recovered_SoundEnvelope {
    u8 opaque_0[77];
    u8 field_4D; /* PS2 +0x4D */
} Recovered_SoundEnvelope;
typedef char assert_Recovered_SoundEnvelope_4D[(((int)&((Recovered_SoundEnvelope *)0)->field_4D) == 77) ? 1 : -1];
#endif
