/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_HASID68_H
#define RECOVERED_HASID68_H
#include "ps2/prelude.h"

typedef struct Recovered_HasId68 {
    u8 opaque_0[104];
    s32 field_68; /* PS2 +0x68 */
} Recovered_HasId68;
typedef char assert_Recovered_HasId68_68[(((int)&((Recovered_HasId68 *)0)->field_68) == 104) ? 1 : -1];
#endif
